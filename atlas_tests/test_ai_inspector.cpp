#include "../editor/panels/AIInspectorPanel.h"
#include <iostream>
#include <cassert>

using namespace atlas::editor;

void test_ai_inspector_create() {
    AIInspectorPanel panel;
    assert(std::string(panel.Name()) == "AI Inspector");
    assert(panel.IsVisible());
    assert(panel.SignalCount() == 0);
    assert(panel.MemoryCount() == 0);
    std::cout << "[PASS] test_ai_inspector_create" << std::endl;
}

void test_ai_inspector_set_sources() {
    AIInspectorPanel panel;
    auto& registry = atlas::ai::AISignalRegistry::Get();
    atlas::ai::AIMemory memory;
    atlas::ai::RelationshipModel relationships;

    panel.SetSignalRegistry(&registry);
    panel.SetMemory(&memory);
    panel.SetRelationshipModel(&relationships);

    // Should not crash
    panel.Refresh();
    std::cout << "[PASS] test_ai_inspector_set_sources" << std::endl;
}

void test_ai_inspector_filter() {
    AIInspectorPanel panel;
    panel.SetSignalFilter("faction");
    assert(panel.SignalFilter() == "faction");
    std::cout << "[PASS] test_ai_inspector_filter" << std::endl;
}

void test_ai_inspector_visibility() {
    AIInspectorPanel panel;
    assert(panel.IsVisible());
    panel.SetVisible(false);
    assert(!panel.IsVisible());
    panel.SetVisible(true);
    assert(panel.IsVisible());
    std::cout << "[PASS] test_ai_inspector_visibility" << std::endl;
}
