#include "AIInspectorPanel.h"

namespace atlas::editor {

void AIInspectorPanel::Draw() {
    // Stub: In a real implementation, this renders via Atlas UI system
    // Layout:
    //   Tab 1 — Signals: Table with Name, Value, Last Updated Tick columns
    //   Tab 2 — Memory:  Table with Key, Value, Strength, Decay Rate columns
    //   Tab 3 — Relationships: Entity pair table
    //   Filter bar at top for signal namespace filtering
    //   Auto-refresh toggle + manual refresh button
}

void AIInspectorPanel::Refresh() {
    m_signalCache.clear();
    m_memoryCache.clear();

    // Note: AISignalRegistry is a singleton — we enumerate known signals.
    // In production, AISignalRegistry would expose an iterator.
    // For now, the panel relies on being populated externally or
    // the registry exposing signal enumeration.

    // Memory snapshot refresh is also dependent on the AIMemory
    // instance providing an iteration interface.
    // The panel structure is ready for when those APIs are available.
}

} // namespace atlas::editor
