#include "ReplayDiff.h"
#include <algorithm>

namespace atlas::graphvm {

ReplayDiffResult CompareReplays(const ReplayCapture& a, const ReplayCapture& b) {
    ReplayDiffResult result;
    result.hashA = a.ComputeHash();
    result.hashB = b.ComputeHash();

    // Fast path: if hashes match, replays are identical
    if (result.hashA == result.hashB && a.EventCount() == b.EventCount()) {
        result.identical = true;
        return result;
    }

    // Compare event by event
    size_t maxEvents = std::max(a.EventCount(), b.EventCount());
    for (size_t i = 0; i < maxEvents; ++i) {
        const ReplayEvent* evA = a.GetEvent(i);
        const ReplayEvent* evB = b.GetEvent(i);

        if (!evA || !evB) {
            // One capture has more events than the other
            ReplayDiffEntry entry;
            entry.tick = evA ? evA->tick : evB->tick;
            entry.graphId = evA ? evA->graphId : evB->graphId;
            entry.eventMismatch = true;
            entry.snapshotMismatch = true;
            result.differences.push_back(std::move(entry));
            result.identical = false;
            continue;
        }

        bool eventDiff = (evA->tick != evB->tick ||
                          evA->graphId != evB->graphId ||
                          evA->eventType != evB->eventType);

        // Compare snapshots
        auto snapDiff = ComputeGraphDiff(evA->snapshot, evB->snapshot);
        bool snapMismatch = snapDiff.HasChanges();

        if (eventDiff || snapMismatch) {
            ReplayDiffEntry entry;
            entry.tick = evA->tick;
            entry.graphId = evA->graphId;
            entry.eventMismatch = eventDiff;
            entry.snapshotMismatch = snapMismatch;
            entry.snapshotDiff = std::move(snapDiff);
            result.differences.push_back(std::move(entry));
            result.identical = false;
        }
    }

    return result;
}

} // namespace atlas::graphvm
