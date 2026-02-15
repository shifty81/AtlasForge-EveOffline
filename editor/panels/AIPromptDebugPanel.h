#pragma once
#include "../ui/EditorPanel.h"
#include "../../engine/ai/LLMContextBuilder.h"
#include "../../engine/ai/LLMResponseValidator.h"
#include "../../engine/ai/LLMCache.h"
#include <string>
#include <vector>

namespace atlas::editor {

/// AIPromptDebugPanel — displays the full LLM context assembly,
/// raw prompt, response, and validation state for debugging.
/// Prompt is immutable.  Output is schema-validated.
/// Apply creates undoable commands.  Replay shows cached output only.
class AIPromptDebugPanel : public EditorPanel {
public:
    const char* Name() const override { return "AI Prompt Debugger"; }
    void Draw() override;

    /// Set the context builder used to assemble prompts.
    void SetContextBuilder(ai::LLMContextBuilder* builder) { m_builder = builder; }

    /// Set the response validator.
    void SetResponseValidator(ai::LLMResponseValidator* validator) { m_validator = validator; }

    /// Set the LLM cache for displaying cached responses.
    void SetCache(ai::LLMCache* cache) { m_cache = cache; }

    /// Set the current raw prompt (assembled, read-only).
    void SetRawPrompt(const std::string& prompt) { m_rawPrompt = prompt; }
    const std::string& RawPrompt() const { return m_rawPrompt; }

    /// Set the last LLM response.
    void SetLastResponse(const std::string& response) { m_lastResponse = response; }
    const std::string& LastResponse() const { return m_lastResponse; }

    /// Set the target graph type for validation display.
    void SetTargetGraphType(const std::string& graphType) { m_targetGraphType = graphType; }
    const std::string& TargetGraphType() const { return m_targetGraphType; }

    /// Return the number of context layers currently active.
    size_t ActiveLayerCount() const;

    /// Get the validation result for the last response.
    ai::LLMValidationResult LastValidationResult() const { return m_lastValidation; }

    /// Run validation on the current response.
    void ValidateResponse();

private:
    ai::LLMContextBuilder* m_builder = nullptr;
    ai::LLMResponseValidator* m_validator = nullptr;
    ai::LLMCache* m_cache = nullptr;

    std::string m_rawPrompt;
    std::string m_lastResponse;
    std::string m_targetGraphType;
    ai::LLMValidationResult m_lastValidation;
};

} // namespace atlas::editor
