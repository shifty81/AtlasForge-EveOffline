#include "../engine/project/ProjectManager.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <filesystem>

using namespace atlas::project;

static void WriteTestProject(const std::string& path, const std::string& content) {
    std::ofstream f(path);
    f << content;
    f.close();
}

void test_project_load_valid() {
    std::string path = "test_project_valid.atlas";
    WriteTestProject(path, R"({
        "schema": "atlas.project.v1",
        "name": "TestGame",
        "version": "1.0.0",
        "description": "A test project",
        "modules": {
            "worldGraph": "world/galaxy.worldgraph",
            "ai": true
        },
        "runtime": {
            "entryWorld": "world/galaxy.worldgraph",
            "tickRate": 60,
            "maxPlayers": 4
        },
        "assets": {
            "root": "game_assets"
        }
    })");

    ProjectManager mgr;
    assert(mgr.Load(path));
    assert(mgr.IsLoaded());
    assert(mgr.Descriptor().schema == "atlas.project.v1");
    assert(mgr.Descriptor().name == "TestGame");
    assert(mgr.Descriptor().version == "1.0.0");
    assert(mgr.Descriptor().description == "A test project");
    assert(mgr.Descriptor().modules.worldGraph == "world/galaxy.worldgraph");
    assert(mgr.Descriptor().modules.ai == true);
    assert(mgr.Descriptor().runtime.entryWorld == "world/galaxy.worldgraph");
    assert(mgr.Descriptor().runtime.tickRate == 60);
    assert(mgr.Descriptor().runtime.maxPlayers == 4);
    assert(mgr.Descriptor().assets.root == "game_assets");

    std::filesystem::remove(path);
    std::cout << "[PASS] test_project_load_valid" << std::endl;
}

void test_project_load_minimal() {
    std::string path = "test_project_minimal.atlas";
    WriteTestProject(path, R"({
        "schema": "atlas.project.v1",
        "name": "Minimal",
        "version": "0.1.0"
    })");

    ProjectManager mgr;
    assert(mgr.Load(path));
    assert(mgr.IsLoaded());
    assert(mgr.Descriptor().name == "Minimal");
    assert(mgr.Descriptor().runtime.tickRate == 30);
    assert(mgr.Descriptor().runtime.maxPlayers == 20);
    assert(mgr.Descriptor().assets.root == "assets");

    std::filesystem::remove(path);
    std::cout << "[PASS] test_project_load_minimal" << std::endl;
}

void test_project_load_missing_file() {
    ProjectManager mgr;
    assert(!mgr.Load("nonexistent.atlas"));
    assert(!mgr.IsLoaded());

    std::cout << "[PASS] test_project_load_missing_file" << std::endl;
}

void test_project_invalid_schema() {
    std::string path = "test_project_bad_schema.atlas";
    WriteTestProject(path, R"({
        "schema": "atlas.project.v99",
        "name": "Bad",
        "version": "1.0.0"
    })");

    ProjectManager mgr;
    assert(!mgr.Load(path));
    assert(!mgr.IsLoaded());

    std::filesystem::remove(path);
    std::cout << "[PASS] test_project_invalid_schema" << std::endl;
}

void test_project_missing_name() {
    std::string path = "test_project_no_name.atlas";
    WriteTestProject(path, R"({
        "schema": "atlas.project.v1",
        "name": "",
        "version": "1.0.0"
    })");

    ProjectManager mgr;
    assert(!mgr.Load(path));

    std::filesystem::remove(path);
    std::cout << "[PASS] test_project_missing_name" << std::endl;
}

void test_project_missing_name_field() {
    std::string path = "test_project_no_name_field.atlas";
    WriteTestProject(path, R"({
        "schema": "atlas.project.v1",
        "version": "1.0.0"
    })");

    ProjectManager mgr;
    assert(!mgr.Load(path));

    std::filesystem::remove(path);
    std::cout << "[PASS] test_project_missing_name_field" << std::endl;
}

void test_project_invalid_version() {
    std::string path = "test_project_bad_ver.atlas";
    WriteTestProject(path, R"({
        "schema": "atlas.project.v1",
        "name": "Bad",
        "version": "abc"
    })");

    ProjectManager mgr;
    assert(!mgr.Load(path));

    std::filesystem::remove(path);
    std::cout << "[PASS] test_project_invalid_version" << std::endl;
}

void test_project_schema_validation() {
    assert(ProjectManager::ValidateSchema("atlas.project.v1"));
    assert(!ProjectManager::ValidateSchema("atlas.project.v2"));
    assert(!ProjectManager::ValidateSchema(""));
    assert(!ProjectManager::ValidateSchema("invalid"));

    std::cout << "[PASS] test_project_schema_validation" << std::endl;
}

void test_project_load_full_modules() {
    std::string path = "test_project_full_modules.atlas";
    WriteTestProject(path, R"({
        "schema": "atlas.project.v1",
        "name": "FullModules",
        "version": "0.12.0",
        "modules": {
            "worldGraph": "worlds/galaxy.worldgraph",
            "tileGraphs": "worlds/",
            "strategyGraphs": "strategy/",
            "conversationGraphs": "conversations/",
            "behaviorGraphs": "ai/",
            "ai": true,
            "content": "data/"
        },
        "runtime": {
            "entryWorld": "worlds/galaxy.worldgraph",
            "tickRate": 30,
            "maxPlayers": 20
        },
        "assets": {
            "root": "assets"
        },
        "config": "config/runtime.json"
    })");

    ProjectManager mgr;
    assert(mgr.Load(path));
    assert(mgr.IsLoaded());
    assert(mgr.Descriptor().modules.worldGraph == "worlds/galaxy.worldgraph");
    assert(mgr.Descriptor().modules.tileGraphs == "worlds/");
    assert(mgr.Descriptor().modules.strategyGraphs == "strategy/");
    assert(mgr.Descriptor().modules.conversationGraphs == "conversations/");
    assert(mgr.Descriptor().modules.behaviorGraphs == "ai/");
    assert(mgr.Descriptor().modules.ai == true);
    assert(mgr.Descriptor().modules.content == "data/");
    assert(mgr.Descriptor().config == "config/runtime.json");

    std::filesystem::remove(path);
    std::cout << "[PASS] test_project_load_full_modules" << std::endl;
}

void test_project_resolve_module_path() {
    std::string dir = "test_resolve_dir";
    std::filesystem::create_directories(dir);
    std::string path = dir + "/test.atlas";
    WriteTestProject(path, R"({
        "schema": "atlas.project.v1",
        "name": "ResolveTest",
        "version": "1.0.0",
        "modules": {
            "worldGraph": "worlds/galaxy.worldgraph"
        }
    })");

    ProjectManager mgr;
    assert(mgr.Load(path));

    std::string resolved = mgr.ResolveModulePath("worlds/galaxy.worldgraph");
    // Should resolve to dir/worlds/galaxy.worldgraph
    assert(resolved.find("test_resolve_dir") != std::string::npos);
    assert(resolved.find("worlds/galaxy.worldgraph") != std::string::npos
        || resolved.find("worlds\\galaxy.worldgraph") != std::string::npos);

    // Empty path should return empty
    assert(mgr.ResolveModulePath("").empty());

    std::filesystem::remove(path);
    std::filesystem::remove_all(dir);
    std::cout << "[PASS] test_project_resolve_module_path" << std::endl;
}

void test_project_unload() {
    std::string path = "test_project_unload.atlas";
    WriteTestProject(path, R"({
        "schema": "atlas.project.v1",
        "name": "UnloadTest",
        "version": "1.0.0"
    })");

    ProjectManager mgr;
    assert(mgr.Load(path));
    assert(mgr.IsLoaded());

    mgr.Unload();
    assert(!mgr.IsLoaded());
    assert(mgr.Descriptor().name.empty());
    assert(mgr.ProjectRoot().empty());

    std::filesystem::remove(path);
    std::cout << "[PASS] test_project_unload" << std::endl;
}
