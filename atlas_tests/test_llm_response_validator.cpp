#include "../engine/ai/LLMResponseValidator.h"
#include <iostream>
#include <cassert>

using namespace atlas::ai;

void test_llm_response_valid_structure() {
    LLMResponseValidator validator;
    auto result = validator.ValidateStructure("{ \"graph\": \"StrategyGraph\" }");
    assert(result.valid);

    std::cout << "[PASS] test_llm_response_valid_structure" << std::endl;
}

void test_llm_response_empty() {
    LLMResponseValidator validator;
    auto result = validator.ValidateStructure("");
    assert(!result.valid);
    assert(result.error == "Response is empty");

    std::cout << "[PASS] test_llm_response_empty" << std::endl;
}

void test_llm_response_not_json_object() {
    LLMResponseValidator validator;
    auto result = validator.ValidateStructure("[1, 2, 3]");
    assert(!result.valid);
    assert(result.error.find("not a JSON object") != std::string::npos);

    std::cout << "[PASS] test_llm_response_not_json_object" << std::endl;
}

void test_llm_response_graph_target_valid() {
    LLMResponseValidator validator;
    validator.AllowGraphType("StrategyGraph");
    auto result = validator.ValidateGraphTarget("StrategyGraph");
    assert(result.valid);

    std::cout << "[PASS] test_llm_response_graph_target_valid" << std::endl;
}

void test_llm_response_graph_target_invalid() {
    LLMResponseValidator validator;
    validator.AllowGraphType("StrategyGraph");
    auto result = validator.ValidateGraphTarget("PhysicsGraph");
    assert(!result.valid);
    assert(result.error.find("not allowed") != std::string::npos);

    std::cout << "[PASS] test_llm_response_graph_target_invalid" << std::endl;
}

void test_llm_response_safety_pass() {
    LLMResponseValidator validator;
    validator.LoadDefaults();
    auto result = validator.ValidateSafety("{ \"changes\": [] }");
    assert(result.valid);

    std::cout << "[PASS] test_llm_response_safety_pass" << std::endl;
}

void test_llm_response_safety_fail() {
    LLMResponseValidator validator;
    validator.LoadDefaults();
    auto result = validator.ValidateSafety("{ \"code\": \"system(\\\"rm -rf\\\")\" }");
    assert(!result.valid);
    assert(result.error.find("forbidden") != std::string::npos);

    std::cout << "[PASS] test_llm_response_safety_fail" << std::endl;
}

void test_llm_response_full_validate() {
    LLMResponseValidator validator;
    validator.LoadDefaults();

    auto result = validator.Validate("{ \"changes\": [] }", "StrategyGraph");
    assert(result.valid);

    std::cout << "[PASS] test_llm_response_full_validate" << std::endl;
}

void test_llm_response_validator_clear() {
    LLMResponseValidator validator;
    validator.LoadDefaults();

    // Valid with defaults
    auto result = validator.ValidateGraphTarget("StrategyGraph");
    assert(result.valid);

    validator.Clear();

    // After clear, nothing is allowed
    result = validator.ValidateGraphTarget("StrategyGraph");
    assert(!result.valid);

    std::cout << "[PASS] test_llm_response_validator_clear" << std::endl;
}
