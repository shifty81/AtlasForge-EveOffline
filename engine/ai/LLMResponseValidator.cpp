#include "LLMResponseValidator.h"
#include <algorithm>

namespace atlas::ai {

LLMValidationResult LLMResponseValidator::ValidateStructure(const std::string& responseJSON) const {
    if (responseJSON.empty()) {
        return {false, "Response is empty"};
    }

    // Minimal structural check: must start with '{' and end with '}'
    size_t first = responseJSON.find_first_not_of(" \t\n\r");
    size_t last = responseJSON.find_last_not_of(" \t\n\r");
    if (first == std::string::npos || last == std::string::npos) {
        return {false, "Response contains only whitespace"};
    }
    if (responseJSON[first] != '{' || responseJSON[last] != '}') {
        return {false, "Response is not a JSON object"};
    }

    return {true, ""};
}

LLMValidationResult LLMResponseValidator::ValidateGraphTarget(const std::string& graphType) const {
    if (graphType.empty()) {
        return {false, "Graph type is empty"};
    }

    for (const auto& allowed : m_allowedGraphTypes) {
        if (allowed == graphType) {
            return {true, ""};
        }
    }

    return {false, "Graph type '" + graphType + "' is not allowed"};
}

LLMValidationResult LLMResponseValidator::ValidateSafety(const std::string& responseJSON) const {
    for (const auto& keyword : m_forbiddenKeywords) {
        if (responseJSON.find(keyword) != std::string::npos) {
            return {false, "Response contains forbidden keyword: " + keyword};
        }
    }

    return {true, ""};
}

LLMValidationResult LLMResponseValidator::Validate(const std::string& responseJSON,
                                                     const std::string& expectedGraphType) const {
    auto structResult = ValidateStructure(responseJSON);
    if (!structResult.valid) return structResult;

    auto graphResult = ValidateGraphTarget(expectedGraphType);
    if (!graphResult.valid) return graphResult;

    auto safetyResult = ValidateSafety(responseJSON);
    if (!safetyResult.valid) return safetyResult;

    return {true, ""};
}

void LLMResponseValidator::AllowGraphType(const std::string& graphType) {
    m_allowedGraphTypes.push_back(graphType);
}

void LLMResponseValidator::AddForbiddenKeyword(const std::string& keyword) {
    m_forbiddenKeywords.push_back(keyword);
}

void LLMResponseValidator::LoadDefaults() {
    m_allowedGraphTypes.clear();
    m_forbiddenKeywords.clear();

    AllowGraphType("StrategyGraph");
    AllowGraphType("ConversationGraph");
    AllowGraphType("WorldGraph");
    AllowGraphType("ShaderGraph");
    AllowGraphType("RenderGraph");
    AllowGraphType("TileGraph");
    AllowGraphType("BehaviorGraph");
    AllowGraphType("SoundGraph");
    AllowGraphType("CharacterGraph");
    AllowGraphType("AnimationGraph");
    AllowGraphType("WeaponGraph");
    AllowGraphType("UIGraph");
    AllowGraphType("GameFlowGraph");

    AddForbiddenKeyword("system(");
    AddForbiddenKeyword("exec(");
    AddForbiddenKeyword("popen(");
    AddForbiddenKeyword("__asm");
    AddForbiddenKeyword("fork(");
    AddForbiddenKeyword("dlopen(");
    AddForbiddenKeyword("#include");
}

void LLMResponseValidator::Clear() {
    m_allowedGraphTypes.clear();
    m_forbiddenKeywords.clear();
}

} // namespace atlas::ai
