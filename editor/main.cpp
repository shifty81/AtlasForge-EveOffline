#include "core/Engine.h"
#include "../engine/core/Logger.h"
#include "../engine/project/ProjectManager.h"
#include <iostream>
#include <string>

static void PrintUsage() {
    std::cout << "Atlas Editor v1.0.0" << std::endl;
    std::cout << "Usage: atlas_editor [options]" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --project <path>     Open a .atlas project file" << std::endl;
    std::cout << "  --help               Show this help message" << std::endl;
}

int main(int argc, char* argv[]) {
    std::string projectPath;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--project" && i + 1 < argc) {
            projectPath = argv[++i];
        } else if (arg == "--help") {
            PrintUsage();
            return 0;
        }
    }

    atlas::Logger::Init();

    // Load project if specified via CLI
    if (!projectPath.empty()) {
        if (!atlas::project::ProjectManager::Get().Load(projectPath)) {
            std::cerr << "Failed to load project: " << projectPath << std::endl;
            return 1;
        }
    }

    atlas::EngineConfig cfg;
    cfg.mode = atlas::EngineMode::Editor;

    if (atlas::project::ProjectManager::Get().IsLoaded()) {
        cfg.tickRate = atlas::project::ProjectManager::Get().Descriptor().runtime.tickRate;
        cfg.assetRoot = atlas::project::ProjectManager::Get().Descriptor().assets.root;
    }

    atlas::Engine engine(cfg);
    engine.InitCore();
    engine.InitRender();
    engine.InitUI();
    engine.InitECS();
    engine.InitNetworking();
    engine.InitEditor();

    engine.Run();

    return 0;
}
