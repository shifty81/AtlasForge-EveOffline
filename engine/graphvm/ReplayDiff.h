#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include "ReplayCapture.h"
#include "GraphDiff.h"

namespace atlas::graphvm {

/// Result of comparing two replay event streams.
struct ReplayDiffEntry {
    uint64_t tick = 0;
    std::string graphId;
    bool eventMismatch = false;    // event type or metadata differs
    bool snapshotMismatch = false; // graph snapshot differs
    GraphDiffResult snapshotDiff;  // structural diff if snapshots differ
};

/// Result of a full replay comparison.
struct ReplayDiffResult {
    bool identical = true;
    uint64_t hashA = 0;
    uint64_t hashB = 0;
    std::vector<ReplayDiffEntry> differences;

    size_t DifferenceCount() const { return differences.size(); }
};

/// Compare two replay captures for determinism verification.
/// Reports all ticks/graphs where the two captures diverge.
ReplayDiffResult CompareReplays(const ReplayCapture& a, const ReplayCapture& b);

} // namespace atlas::graphvm
