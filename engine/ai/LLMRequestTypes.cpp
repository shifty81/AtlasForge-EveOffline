#include "LLMRequestTypes.h"

namespace atlas::ai {

void LLMRequestTypeEnforcer::AllowRequestType(const std::string& toolContext, LLMRequestType type) {
    m_allowed[toolContext].insert(static_cast<int>(type));
}

bool LLMRequestTypeEnforcer::IsAllowed(const std::string& toolContext, LLMRequestType type) const {
    auto it = m_allowed.find(toolContext);
    if (it == m_allowed.end()) return false;
    return it->second.count(static_cast<int>(type)) > 0;
}

void LLMRequestTypeEnforcer::RegisterDefaults() {
    // StrategyGraph Editor
    AllowRequestType("StrategyGraphEditor", LLMRequestType::GenerateStrategyGraph);
    AllowRequestType("StrategyGraphEditor", LLMRequestType::LintAIBehavior);

    // ConversationGraph Editor
    AllowRequestType("ConversationGraphEditor", LLMRequestType::GenerateConversationGraph);

    // ShaderGraph Editor
    AllowRequestType("ShaderGraphEditor", LLMRequestType::ValidateShaderGraph);

    // WorldGraph Editor
    AllowRequestType("WorldGraphEditor", LLMRequestType::SuggestWorldGraphNodes);

    // AI Inspector
    AllowRequestType("AIInspector", LLMRequestType::ExplainSystem);
    AllowRequestType("AIInspector", LLMRequestType::SummarizeAIMemory);
}

void LLMRequestTypeEnforcer::Clear() {
    m_allowed.clear();
}

size_t LLMRequestTypeEnforcer::RuleCount() const {
    size_t count = 0;
    for (const auto& pair : m_allowed) {
        count += pair.second.size();
    }
    return count;
}

} // namespace atlas::ai
