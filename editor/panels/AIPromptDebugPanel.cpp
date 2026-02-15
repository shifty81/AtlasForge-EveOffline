#include "AIPromptDebugPanel.h"

namespace atlas::editor {

void AIPromptDebugPanel::Draw() {
    // Stub: In a real implementation, this renders via Atlas UI system
    // Layout:
    //   Section 1 — Context Layer Checklist:
    //     ✓/✗ for each LLMContextLayer present in the builder
    //   Section 2 — Raw Prompt (read-only text area):
    //     Full assembled prompt from BuildFinalPrompt()
    //   Section 3 — LLM Response (read-only):
    //     Structured JSON response from LLM
    //   Section 4 — Validation Status:
    //     Shows valid/invalid + error message
    //   Section 5 — Action Buttons:
    //     [Apply] — creates undoable command from response
    //     [Reject] — discards response
}

size_t AIPromptDebugPanel::ActiveLayerCount() const {
    if (!m_builder) return 0;
    return m_builder->BlockCount();
}

void AIPromptDebugPanel::ValidateResponse() {
    if (!m_validator) {
        m_lastValidation = {false, "No validator set"};
        return;
    }
    m_lastValidation = m_validator->Validate(m_lastResponse, m_targetGraphType);
}

} // namespace atlas::editor
