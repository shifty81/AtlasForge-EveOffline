#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace atlas::ai {

/// All LLM usage must declare a request type — no free chat.
enum class LLMRequestType {
    ExplainSystem,
    GenerateStrategyGraph,
    GenerateConversationGraph,
    ValidateShaderGraph,
    SuggestWorldGraphNodes,
    LintAIBehavior,
    SummarizeAIMemory
};

/// Enforces which request types each tool context is allowed to issue.
class LLMRequestTypeEnforcer {
public:
    void AllowRequestType(const std::string& toolContext, LLMRequestType type);

    bool IsAllowed(const std::string& toolContext, LLMRequestType type) const;

    /// Register the default Atlas tool→request mappings.
    void RegisterDefaults();

    void Clear();

    size_t RuleCount() const;

private:
    std::unordered_map<std::string, std::unordered_set<int>> m_allowed;
};

} // namespace atlas::ai
