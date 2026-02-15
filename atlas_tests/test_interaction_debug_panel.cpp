#include "../editor/panels/InteractionDebugPanel.h"
#include <iostream>
#include <cassert>

using namespace atlas::editor;

void test_interaction_debug_empty() {
    InteractionDebugPanel panel;
    assert(panel.LogSize() == 0);
    assert(panel.GetLog().empty());
    std::cout << "[PASS] test_interaction_debug_empty" << std::endl;
}

void test_interaction_debug_log_entry() {
    InteractionDebugPanel panel;
    InteractionLogEntry entry;
    entry.speaker = "Player";
    entry.text = "select all fighters";
    entry.resolvedIntent = "select_units";
    entry.confidence = 0.95f;
    panel.LogInteraction(entry);
    assert(panel.LogSize() == 1);
    assert(panel.GetLog()[0].speaker == "Player");
    assert(panel.GetLog()[0].text == "select all fighters");
    assert(panel.GetLog()[0].resolvedIntent == "select_units");
    std::cout << "[PASS] test_interaction_debug_log_entry" << std::endl;
}

void test_interaction_debug_multiple_entries() {
    InteractionDebugPanel panel;
    panel.LogInteraction({"Player", "attack", "attack_target", 0.9f});
    panel.LogInteraction({"NPC", "retreat", "flee", 0.8f});
    panel.LogInteraction({"Player", "dock", "dock_station", 1.0f});
    assert(panel.LogSize() == 3);
    assert(panel.GetLog()[1].speaker == "NPC");
    assert(panel.GetLog()[2].resolvedIntent == "dock_station");
    std::cout << "[PASS] test_interaction_debug_multiple_entries" << std::endl;
}

void test_interaction_debug_clear_log() {
    InteractionDebugPanel panel;
    panel.LogInteraction({"Player", "test", "test_intent", 1.0f});
    panel.LogInteraction({"Player", "test2", "test_intent2", 1.0f});
    assert(panel.LogSize() == 2);
    panel.ClearLog();
    assert(panel.LogSize() == 0);
    assert(panel.GetLog().empty());
    std::cout << "[PASS] test_interaction_debug_clear_log" << std::endl;
}

void test_interaction_debug_panel_name() {
    InteractionDebugPanel panel;
    assert(std::string(panel.Name()) == "Interaction Debugger");
    std::cout << "[PASS] test_interaction_debug_panel_name" << std::endl;
}

void test_interaction_debug_visibility() {
    InteractionDebugPanel panel;
    assert(panel.IsVisible());
    panel.SetVisible(false);
    assert(!panel.IsVisible());
    panel.SetVisible(true);
    assert(panel.IsVisible());
    std::cout << "[PASS] test_interaction_debug_visibility" << std::endl;
}
