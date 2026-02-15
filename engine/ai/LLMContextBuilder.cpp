#include "LLMContextBuilder.h"

namespace atlas::ai {

void LLMContextBuilder::Reset() {
    m_blocks.clear();
}

void LLMContextBuilder::AddEngineConstitution() {
    m_blocks.push_back({
        LLMContextLayer::EngineConstitution,
        "You are an assistant for Atlas Engine.\n"
        "\n"
        "Rules:\n"
        "- You may generate data, graphs, schemas, or explanations.\n"
        "- You may NOT generate executable engine logic.\n"
        "- StrategyGraph is the sole decision authority.\n"
        "- ConversationGraph emits state only.\n"
        "- Determinism is mandatory.\n"
        "- If uncertain, ask for clarification."
    });
}

void LLMContextBuilder::AddSystemContracts() {
    m_blocks.push_back({
        LLMContextLayer::SystemContracts,
        "Atlas Systems:\n"
        "- StrategyGraph: authoritative AI decision logic\n"
        "- ConversationGraph: dialogue + memory emission\n"
        "- RenderGraph: GPU execution graph\n"
        "- WorldGraph: world generation logic\n"
        "- AISignals: read-only numeric inputs"
    });
}

void LLMContextBuilder::AddSchemaDefinitions(const std::string& schemaName) {
    m_blocks.push_back({
        LLMContextLayer::SchemaDefinitions,
        "Active Schema: " + schemaName
    });
}

void LLMContextBuilder::AddToolContext(const std::string& toolName) {
    m_blocks.push_back({
        LLMContextLayer::ToolContext,
        "Current Tool: " + toolName
    });
}

void LLMContextBuilder::AddRuntimeSummary(const std::string& summaryJSON) {
    m_blocks.push_back({
        LLMContextLayer::RuntimeSummary,
        "Runtime Summary:\n" + summaryJSON
    });
}

void LLMContextBuilder::AddUserPrompt(const std::string& prompt) {
    m_blocks.push_back({
        LLMContextLayer::UserPrompt,
        "User Request:\n" + prompt
    });
}

std::string LLMContextBuilder::BuildFinalPrompt() const {
    std::string result;
    for (const auto& block : m_blocks) {
        result += "\n\n---\n\n";
        result += block.content;
    }
    return result;
}

} // namespace atlas::ai
