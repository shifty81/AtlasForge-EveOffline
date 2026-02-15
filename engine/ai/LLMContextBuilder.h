#pragma once
#include <string>
#include <vector>

namespace atlas::ai {

enum class LLMContextLayer {
    EngineConstitution,
    SystemContracts,
    SchemaDefinitions,
    ToolContext,
    RuntimeSummary,
    UserPrompt
};

struct LLMContextBlock {
    LLMContextLayer layer;
    std::string content;
};

/// AtlasLLMContextBuilder — assembles a deterministic, layered context
/// for any LLM request in Atlas.  Context is read-only once built.
class LLMContextBuilder {
public:
    void Reset();

    void AddEngineConstitution();
    void AddSystemContracts();
    void AddSchemaDefinitions(const std::string& schemaName);
    void AddToolContext(const std::string& toolName);
    void AddRuntimeSummary(const std::string& summaryJSON);
    void AddUserPrompt(const std::string& prompt);

    std::string BuildFinalPrompt() const;

    size_t BlockCount() const { return m_blocks.size(); }
    const std::vector<LLMContextBlock>& Blocks() const { return m_blocks; }

private:
    std::vector<LLMContextBlock> m_blocks;
};

} // namespace atlas::ai
