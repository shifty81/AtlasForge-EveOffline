#include "../editor/panels/VoiceCommandPanel.h"
#include <iostream>
#include <cassert>

using namespace atlas::editor;
using namespace atlas::voice;
using namespace atlas::interaction;

void test_voice_panel_create() {
    VoiceCommandRegistry voiceReg;
    IntentRegistry intentReg;
    VoiceCommandPanel panel(voiceReg, intentReg);
    assert(std::string(panel.Name()) == "Voice Commands");
    assert(!panel.IsListening());
    std::cout << "[PASS] test_voice_panel_create" << std::endl;
}

void test_voice_panel_listen_toggle() {
    VoiceCommandRegistry voiceReg;
    IntentRegistry intentReg;
    VoiceCommandPanel panel(voiceReg, intentReg);
    assert(!panel.IsListening());
    panel.SetListening(true);
    assert(panel.IsListening());
    panel.SetListening(false);
    assert(!panel.IsListening());
    std::cout << "[PASS] test_voice_panel_listen_toggle" << std::endl;
}

void test_voice_panel_process_match() {
    VoiceCommandRegistry voiceReg;
    IntentRegistry intentReg;
    voiceReg.Register({"attack target", "attack", "game"});

    bool dispatched = false;
    intentReg.Register("attack", [&](const Intent&) { dispatched = true; });

    VoiceCommandPanel panel(voiceReg, intentReg);
    panel.ProcessPhrase("attack target");
    assert(panel.LastPhrase() == "attack target");
    assert(panel.LastResolvedIntent() == "attack");
    assert(dispatched);
    std::cout << "[PASS] test_voice_panel_process_match" << std::endl;
}

void test_voice_panel_process_no_match() {
    VoiceCommandRegistry voiceReg;
    IntentRegistry intentReg;

    VoiceCommandPanel panel(voiceReg, intentReg);
    panel.ProcessPhrase("unknown phrase");
    assert(panel.LastPhrase() == "unknown phrase");
    assert(panel.LastResolvedIntent().empty());
    std::cout << "[PASS] test_voice_panel_process_no_match" << std::endl;
}

void test_voice_panel_pipeline_voice_to_intent() {
    VoiceCommandRegistry voiceReg;
    IntentRegistry intentReg;

    voiceReg.Register({"select all", "select_units", "game"});
    voiceReg.Register({"zoom out", "camera_zoom", "editor"});

    std::string lastIntent;
    intentReg.Register("select_units", [&](const Intent& i) {
        lastIntent = i.name;
    });
    intentReg.Register("camera_zoom", [&](const Intent& i) {
        lastIntent = i.name;
    });

    VoiceCommandPanel panel(voiceReg, intentReg);

    panel.ProcessPhrase("select all");
    assert(lastIntent == "select_units");
    assert(panel.LastResolvedIntent() == "select_units");

    panel.ProcessPhrase("zoom out");
    assert(lastIntent == "camera_zoom");
    assert(panel.LastResolvedIntent() == "camera_zoom");
    std::cout << "[PASS] test_voice_panel_pipeline_voice_to_intent" << std::endl;
}

void test_voice_panel_visibility() {
    VoiceCommandRegistry voiceReg;
    IntentRegistry intentReg;
    VoiceCommandPanel panel(voiceReg, intentReg);
    assert(panel.IsVisible());
    panel.SetVisible(false);
    assert(!panel.IsVisible());
    std::cout << "[PASS] test_voice_panel_visibility" << std::endl;
}
