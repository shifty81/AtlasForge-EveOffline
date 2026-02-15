#pragma once
#include "../ui/EditorPanel.h"
#include "../../engine/ai/AISignalRegistry.h"
#include "../../engine/ai/AIMemory.h"
#include "../../engine/ai/RelationshipModel.h"
#include <string>
#include <vector>

namespace atlas::editor {

/// AIInspectorPanel — displays AI state for debugging.
/// Shows signals, memory entries, relationships, and behavior graph states.
class AIInspectorPanel : public EditorPanel {
public:
    const char* Name() const override { return "AI Inspector"; }
    void Draw() override;

    /// Refresh cached data from the AI subsystems.
    void Refresh();

    /// Set data sources
    void SetSignalRegistry(ai::AISignalRegistry* registry) { m_signals = registry; }
    void SetMemory(ai::AIMemory* memory) { m_memory = memory; }
    void SetRelationshipModel(ai::RelationshipModel* model) { m_relationships = model; }

    /// Cached signal snapshot for display
    struct SignalSnapshot {
        std::string name;
        float value;
        uint64_t lastTick;
    };

    /// Cached memory snapshot for display
    struct MemorySnapshot {
        std::string key;
        std::string value;
        float strength;
        float decayRate;
    };

    const std::vector<SignalSnapshot>& GetSignals() const { return m_signalCache; }
    const std::vector<MemorySnapshot>& GetMemories() const { return m_memoryCache; }

    size_t SignalCount() const { return m_signalCache.size(); }
    size_t MemoryCount() const { return m_memoryCache.size(); }

    /// Filter signals by namespace prefix
    void SetSignalFilter(const std::string& filter) { m_signalFilter = filter; }
    const std::string& SignalFilter() const { return m_signalFilter; }

private:
    ai::AISignalRegistry* m_signals = nullptr;
    ai::AIMemory* m_memory = nullptr;
    ai::RelationshipModel* m_relationships = nullptr;

    std::vector<SignalSnapshot> m_signalCache;
    std::vector<MemorySnapshot> m_memoryCache;
    std::string m_signalFilter;
};

} // namespace atlas::editor
