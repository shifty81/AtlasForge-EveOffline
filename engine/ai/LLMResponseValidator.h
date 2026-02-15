#pragma once
#include <string>
#include <vector>

namespace atlas::ai {

/// Validation result for an LLM response.
struct LLMValidationResult {
    bool valid = false;
    std::string error;
};

/// Validates LLM responses against schema and safety rules.
/// LLM outputs must be structured JSON conforming to graph schemas.
/// Responses that attempt to mutate world state or execute code are rejected.
class LLMResponseValidator {
public:
    /// Validate that response is well-formed JSON with expected structure.
    LLMValidationResult ValidateStructure(const std::string& responseJSON) const;

    /// Validate that a response targets an allowed graph type.
    LLMValidationResult ValidateGraphTarget(const std::string& graphType) const;

    /// Validate that a response contains no forbidden operations.
    LLMValidationResult ValidateSafety(const std::string& responseJSON) const;

    /// Full validation pipeline: structure + graph target + safety.
    LLMValidationResult Validate(const std::string& responseJSON,
                                  const std::string& expectedGraphType) const;

    /// Register an allowed graph type (e.g. "StrategyGraph").
    void AllowGraphType(const std::string& graphType);

    /// Register a forbidden keyword (e.g. "system(", "exec(").
    void AddForbiddenKeyword(const std::string& keyword);

    /// Load default allowed graph types and forbidden keywords.
    void LoadDefaults();

    void Clear();

private:
    std::vector<std::string> m_allowedGraphTypes;
    std::vector<std::string> m_forbiddenKeywords;
};

} // namespace atlas::ai
