#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include "GraphDiff.h"

namespace atlas::graphvm {

/// A single recorded event in an AI replay capture.
struct ReplayEvent {
    uint64_t tick = 0;
    std::string graphId;
    std::string eventType;   // "execute", "propose", "approve", "reject"
    GraphSnapshot snapshot;
    std::string metadata;    // optional JSON metadata
};

/// AI Replay Capture — records deterministic graph events for replay.
/// Captures graph snapshots and AI decisions at each tick for later
/// playback, debugging, and determinism verification.
class ReplayCapture {
public:
    /// Record an event at the current tick.
    void Record(uint64_t tick, const std::string& graphId,
                const std::string& eventType,
                const GraphSnapshot& snapshot,
                const std::string& metadata = "");

    /// Get event count.
    size_t EventCount() const;

    /// Get event by index.
    const ReplayEvent* GetEvent(size_t index) const;

    /// Get all events for a specific graph.
    std::vector<const ReplayEvent*> GetByGraph(const std::string& graphId) const;

    /// Get all events at a specific tick.
    std::vector<const ReplayEvent*> GetByTick(uint64_t tick) const;

    /// Get all events in a tick range [startTick, endTick].
    std::vector<const ReplayEvent*> GetByTickRange(uint64_t startTick, uint64_t endTick) const;

    /// Get the tick range [min, max] of recorded events.
    /// Returns {0, 0} if empty.
    std::pair<uint64_t, uint64_t> TickRange() const;

    /// Compute a deterministic hash of all recorded events.
    /// Used for replay determinism verification.
    uint64_t ComputeHash() const;

    /// Clear all recorded events.
    void Clear();

private:
    std::vector<ReplayEvent> m_events;
};

} // namespace atlas::graphvm
