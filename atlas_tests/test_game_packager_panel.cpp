#include "../editor/tools/GamePackagerPanel.h"
#include <iostream>
#include <cassert>

using namespace atlas::editor;

void test_game_packager_name() {
    GamePackagerPanel panel;
    assert(std::string(panel.Name()) == "Game Packager");
    std::cout << "[PASS] test_game_packager_name" << std::endl;
}

void test_game_packager_default_settings() {
    GamePackagerPanel panel;
    const auto& settings = panel.Settings();
    assert(settings.target == BuildTarget::Client);
    assert(settings.mode == BuildMode::Debug);
    assert(settings.singleExe == false);
    assert(settings.includeMods == false);
    assert(settings.stripEditorData == true);
    assert(settings.outputPath == "./build/output");
    std::cout << "[PASS] test_game_packager_default_settings" << std::endl;
}

void test_game_packager_visibility() {
    GamePackagerPanel panel;
    assert(panel.IsVisible());
    panel.SetVisible(false);
    assert(!panel.IsVisible());
    panel.SetVisible(true);
    assert(panel.IsVisible());
    std::cout << "[PASS] test_game_packager_visibility" << std::endl;
}
