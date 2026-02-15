#include "../engine/ai/LLMContextBuilder.h"
#include <iostream>
#include <cassert>

using namespace atlas::ai;

void test_llm_context_builder_reset() {
    LLMContextBuilder builder;
    assert(builder.BlockCount() == 0);

    builder.AddEngineConstitution();
    assert(builder.BlockCount() == 1);

    builder.Reset();
    assert(builder.BlockCount() == 0);

    std::cout << "[PASS] test_llm_context_builder_reset" << std::endl;
}

void test_llm_context_builder_add_layers() {
    LLMContextBuilder builder;

    builder.AddEngineConstitution();
    builder.AddSystemContracts();
    builder.AddSchemaDefinitions("atlas.strategygraph.v1");
    builder.AddToolContext("StrategyGraphEditor");
    builder.AddRuntimeSummary("{\"tick\":100}");
    builder.AddUserPrompt("Make this trader cautious");

    assert(builder.BlockCount() == 6);

    // Verify layer types
    const auto& blocks = builder.Blocks();
    assert(blocks[0].layer == LLMContextLayer::EngineConstitution);
    assert(blocks[1].layer == LLMContextLayer::SystemContracts);
    assert(blocks[2].layer == LLMContextLayer::SchemaDefinitions);
    assert(blocks[3].layer == LLMContextLayer::ToolContext);
    assert(blocks[4].layer == LLMContextLayer::RuntimeSummary);
    assert(blocks[5].layer == LLMContextLayer::UserPrompt);

    std::cout << "[PASS] test_llm_context_builder_add_layers" << std::endl;
}

void test_llm_context_builder_build_prompt() {
    LLMContextBuilder builder;
    builder.AddEngineConstitution();
    builder.AddUserPrompt("Help me");

    std::string prompt = builder.BuildFinalPrompt();
    assert(!prompt.empty());
    assert(prompt.find("Atlas Engine") != std::string::npos);
    assert(prompt.find("User Request:") != std::string::npos);
    assert(prompt.find("Help me") != std::string::npos);

    std::cout << "[PASS] test_llm_context_builder_build_prompt" << std::endl;
}

void test_llm_context_builder_schema_content() {
    LLMContextBuilder builder;
    builder.AddSchemaDefinitions("atlas.worldgraph.v1");

    std::string prompt = builder.BuildFinalPrompt();
    assert(prompt.find("atlas.worldgraph.v1") != std::string::npos);

    std::cout << "[PASS] test_llm_context_builder_schema_content" << std::endl;
}

void test_llm_context_builder_empty_prompt() {
    LLMContextBuilder builder;
    std::string prompt = builder.BuildFinalPrompt();
    assert(prompt.empty());

    std::cout << "[PASS] test_llm_context_builder_empty_prompt" << std::endl;
}
