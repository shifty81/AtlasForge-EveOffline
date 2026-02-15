#pragma once
#include "GraphDiff.h"
#include <cstdint>
#include <vector>
#include <string>

namespace atlas::graphvm {

/// A single frame in the graph execution timeline.
struct TimelineFrame {
    uint64_t tick;
    GraphSnapshot snapshot;
    std::string label;   // optional human-readable label
};

/// GraphTimeline — records graph snapshots over time for replay/scrubbing.
class GraphTimeline {
public:
    /// Record a snapshot at the given tick.
    void RecordFrame(uint64_t tick, const GraphSnapshot& snapshot, const std::string& label = "");

    /// Get the number of recorded frames.
    size_t FrameCount() const;

    /// Get a frame by index (0-based).
    const TimelineFrame* GetFrame(size_t index) const;

    /// Get the frame at a specific tick, or nullptr if not found.
    const TimelineFrame* GetFrameAtTick(uint64_t tick) const;

    /// Get the current scrubber position (frame index).
    size_t CurrentIndex() const;

    /// Set the scrubber position to a specific frame index.
    bool SeekTo(size_t index);

    /// Step forward by one frame. Returns false if at end.
    bool StepForward();

    /// Step backward by one frame. Returns false if at beginning.
    bool StepBackward();

    /// Seek to the first frame.
    void SeekToBeginning();

    /// Seek to the last frame.
    void SeekToEnd();

    /// Get the current frame (at scrubber position).
    const TimelineFrame* CurrentFrame() const;

    /// Compute the diff between the current frame and the next.
    /// Returns empty diff if at the last frame or no frames exist.
    GraphDiffResult DiffToNext() const;

    /// Compute the diff between the previous frame and current.
    /// Returns empty diff if at the first frame or no frames exist.
    GraphDiffResult DiffFromPrevious() const;

    /// Clear all recorded frames and reset scrubber.
    void Clear();

    /// Get the tick range (first tick, last tick).
    /// Returns (0, 0) if no frames.
    std::pair<uint64_t, uint64_t> TickRange() const;

private:
    std::vector<TimelineFrame> m_frames;
    size_t m_currentIndex = 0;
};

} // namespace atlas::graphvm
