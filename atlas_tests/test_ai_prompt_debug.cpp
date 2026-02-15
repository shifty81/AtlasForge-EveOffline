#include "../editor/panels/AIPromptDebugPanel.h"
#include <iostream>
#include <cassert>

using namespace atlas::editor;

void test_ai_prompt_debug_create() {
    AIPromptDebugPanel panel;
    assert(std::string(panel.Name()) == "AI Prompt Debugger");
    assert(panel.IsVisible());
    assert(panel.ActiveLayerCount() == 0);
    assert(panel.RawPrompt().empty());
    assert(panel.LastResponse().empty());
    std::cout << "[PASS] test_ai_prompt_debug_create" << std::endl;
}

void test_ai_prompt_debug_set_sources() {
    AIPromptDebugPanel panel;
    atlas::ai::LLMContextBuilder builder;
    atlas::ai::LLMResponseValidator validator;
    atlas::ai::LLMCache cache;

    panel.SetContextBuilder(&builder);
    panel.SetResponseValidator(&validator);
    panel.SetCache(&cache);

    // Should not crash
    panel.Draw();
    std::cout << "[PASS] test_ai_prompt_debug_set_sources" << std::endl;
}

void test_ai_prompt_debug_layer_count() {
    AIPromptDebugPanel panel;
    atlas::ai::LLMContextBuilder builder;
    panel.SetContextBuilder(&builder);

    assert(panel.ActiveLayerCount() == 0);

    builder.AddEngineConstitution();
    builder.AddSystemContracts();
    assert(panel.ActiveLayerCount() == 2);

    builder.AddUserPrompt("test");
    assert(panel.ActiveLayerCount() == 3);

    std::cout << "[PASS] test_ai_prompt_debug_layer_count" << std::endl;
}

void test_ai_prompt_debug_raw_prompt() {
    AIPromptDebugPanel panel;
    panel.SetRawPrompt("assembled prompt text");
    assert(panel.RawPrompt() == "assembled prompt text");
    std::cout << "[PASS] test_ai_prompt_debug_raw_prompt" << std::endl;
}

void test_ai_prompt_debug_response() {
    AIPromptDebugPanel panel;
    panel.SetLastResponse("{ \"changes\": [] }");
    assert(panel.LastResponse() == "{ \"changes\": [] }");
    std::cout << "[PASS] test_ai_prompt_debug_response" << std::endl;
}

void test_ai_prompt_debug_validate() {
    AIPromptDebugPanel panel;
    atlas::ai::LLMResponseValidator validator;
    validator.LoadDefaults();

    panel.SetResponseValidator(&validator);
    panel.SetLastResponse("{ \"changes\": [] }");
    panel.SetTargetGraphType("StrategyGraph");

    panel.ValidateResponse();
    assert(panel.LastValidationResult().valid);

    // Test invalid graph type
    panel.SetTargetGraphType("PhysicsGraph");
    panel.ValidateResponse();
    assert(!panel.LastValidationResult().valid);

    std::cout << "[PASS] test_ai_prompt_debug_validate" << std::endl;
}

void test_ai_prompt_debug_visibility() {
    AIPromptDebugPanel panel;
    assert(panel.IsVisible());
    panel.SetVisible(false);
    assert(!panel.IsVisible());
    panel.SetVisible(true);
    assert(panel.IsVisible());
    std::cout << "[PASS] test_ai_prompt_debug_visibility" << std::endl;
}
