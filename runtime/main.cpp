#include "../engine/core/Engine.h"
#include "../engine/core/Logger.h"
#include "../engine/project/ProjectManager.h"
#include <iostream>
#include <string>

static void PrintUsage() {
    std::cout << "Atlas Runtime v1.0.0" << std::endl;
    std::cout << "Usage: atlas_runtime [options]" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --project <path>     Load a .atlas project file" << std::endl;
    std::cout << "  --mode <mode>        Runtime mode: client, server (default: client)" << std::endl;
    std::cout << "  --validate-only      Validate project and exit" << std::endl;
    std::cout << "  --info               Display project info and exit" << std::endl;
    std::cout << "  --help               Show this help message" << std::endl;
}

static void PrintProjectInfo(const atlas::project::ProjectDescriptor& desc, const std::string& root) {
    std::cout << "Project: " << desc.name << std::endl;
    std::cout << "Version: " << desc.version << std::endl;
    if (!desc.description.empty())
        std::cout << "Description: " << desc.description << std::endl;
    std::cout << "Root: " << root << std::endl;
    std::cout << std::endl;
    std::cout << "Modules:" << std::endl;
    if (!desc.modules.worldGraph.empty())
        std::cout << "  worldGraph: " << desc.modules.worldGraph << std::endl;
    if (!desc.modules.tileGraphs.empty())
        std::cout << "  tileGraphs: " << desc.modules.tileGraphs << std::endl;
    if (!desc.modules.strategyGraphs.empty())
        std::cout << "  strategyGraphs: " << desc.modules.strategyGraphs << std::endl;
    if (!desc.modules.conversationGraphs.empty())
        std::cout << "  conversationGraphs: " << desc.modules.conversationGraphs << std::endl;
    if (!desc.modules.behaviorGraphs.empty())
        std::cout << "  behaviorGraphs: " << desc.modules.behaviorGraphs << std::endl;
    std::cout << "  ai: " << (desc.modules.ai ? "true" : "false") << std::endl;
    if (!desc.modules.content.empty())
        std::cout << "  content: " << desc.modules.content << std::endl;
    std::cout << std::endl;
    std::cout << "Runtime:" << std::endl;
    if (!desc.runtime.entryWorld.empty())
        std::cout << "  entryWorld: " << desc.runtime.entryWorld << std::endl;
    std::cout << "  tickRate: " << desc.runtime.tickRate << std::endl;
    std::cout << "  maxPlayers: " << desc.runtime.maxPlayers << std::endl;
    std::cout << std::endl;
    std::cout << "Assets:" << std::endl;
    std::cout << "  root: " << desc.assets.root << std::endl;
    if (!desc.config.empty())
        std::cout << "Config: " << desc.config << std::endl;
}

int main(int argc, char* argv[]) {
    std::string projectPath;
    std::string modeStr = "client";
    bool validateOnly = false;
    bool showInfo = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--project" && i + 1 < argc) {
            projectPath = argv[++i];
        } else if (arg == "--mode" && i + 1 < argc) {
            modeStr = argv[++i];
        } else if (arg == "--validate-only") {
            validateOnly = true;
        } else if (arg == "--info") {
            showInfo = true;
        } else if (arg == "--help") {
            PrintUsage();
            return 0;
        }
    }

    atlas::Logger::Init();

    // Load project if specified
    if (!projectPath.empty()) {
        if (!atlas::project::ProjectManager::Get().Load(projectPath)) {
            std::cerr << "Failed to load project: " << projectPath << std::endl;
            return 1;
        }

        if (validateOnly) {
            std::cout << "Project validation passed: "
                      << atlas::project::ProjectManager::Get().Descriptor().name << std::endl;
            return 0;
        }

        if (showInfo) {
            PrintProjectInfo(
                atlas::project::ProjectManager::Get().Descriptor(),
                atlas::project::ProjectManager::Get().ProjectRoot());
            return 0;
        }
    }

    // Determine engine mode
    atlas::EngineMode engineMode = atlas::EngineMode::Client;
    if (modeStr == "server") {
        engineMode = atlas::EngineMode::Server;
    }

    // Configure engine
    atlas::EngineConfig cfg;
    cfg.mode = engineMode;

    if (atlas::project::ProjectManager::Get().IsLoaded()) {
        const auto& desc = atlas::project::ProjectManager::Get().Descriptor();
        cfg.tickRate = desc.runtime.tickRate;
        cfg.assetRoot = atlas::project::ProjectManager::Get().ResolveModulePath(desc.assets.root);
    }

    // Initialize and run
    atlas::Engine engine(cfg);
    engine.InitCore();
    engine.InitECS();
    engine.InitNetworking();

    atlas::Logger::Info("Atlas Runtime starting...");
    engine.Run();

    return 0;
}
