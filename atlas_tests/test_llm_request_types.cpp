#include "../engine/ai/LLMRequestTypes.h"
#include <iostream>
#include <cassert>

using namespace atlas::ai;

void test_llm_request_type_allow() {
    LLMRequestTypeEnforcer enforcer;
    enforcer.AllowRequestType("TestTool", LLMRequestType::ExplainSystem);

    assert(enforcer.IsAllowed("TestTool", LLMRequestType::ExplainSystem));
    assert(!enforcer.IsAllowed("TestTool", LLMRequestType::GenerateStrategyGraph));
    assert(!enforcer.IsAllowed("OtherTool", LLMRequestType::ExplainSystem));

    std::cout << "[PASS] test_llm_request_type_allow" << std::endl;
}

void test_llm_request_type_defaults() {
    LLMRequestTypeEnforcer enforcer;
    enforcer.RegisterDefaults();

    // StrategyGraph Editor should allow GenerateStrategyGraph
    assert(enforcer.IsAllowed("StrategyGraphEditor", LLMRequestType::GenerateStrategyGraph));
    assert(enforcer.IsAllowed("StrategyGraphEditor", LLMRequestType::LintAIBehavior));
    assert(!enforcer.IsAllowed("StrategyGraphEditor", LLMRequestType::ValidateShaderGraph));

    // AI Inspector should allow ExplainSystem
    assert(enforcer.IsAllowed("AIInspector", LLMRequestType::ExplainSystem));
    assert(enforcer.IsAllowed("AIInspector", LLMRequestType::SummarizeAIMemory));
    assert(!enforcer.IsAllowed("AIInspector", LLMRequestType::GenerateStrategyGraph));

    std::cout << "[PASS] test_llm_request_type_defaults" << std::endl;
}

void test_llm_request_type_clear() {
    LLMRequestTypeEnforcer enforcer;
    enforcer.RegisterDefaults();
    assert(enforcer.RuleCount() > 0);

    enforcer.Clear();
    assert(enforcer.RuleCount() == 0);
    assert(!enforcer.IsAllowed("StrategyGraphEditor", LLMRequestType::GenerateStrategyGraph));

    std::cout << "[PASS] test_llm_request_type_clear" << std::endl;
}

void test_llm_request_type_unknown_tool() {
    LLMRequestTypeEnforcer enforcer;
    enforcer.RegisterDefaults();

    assert(!enforcer.IsAllowed("UnknownTool", LLMRequestType::ExplainSystem));
    assert(!enforcer.IsAllowed("", LLMRequestType::ExplainSystem));

    std::cout << "[PASS] test_llm_request_type_unknown_tool" << std::endl;
}
