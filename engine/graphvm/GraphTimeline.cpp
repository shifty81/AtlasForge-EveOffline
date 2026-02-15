#include "GraphTimeline.h"

namespace atlas::graphvm {

void GraphTimeline::RecordFrame(uint64_t tick, const GraphSnapshot& snapshot, const std::string& label) {
    m_frames.push_back({tick, snapshot, label});
    m_currentIndex = m_frames.size() - 1;
}

size_t GraphTimeline::FrameCount() const {
    return m_frames.size();
}

const TimelineFrame* GraphTimeline::GetFrame(size_t index) const {
    if (index >= m_frames.size()) return nullptr;
    return &m_frames[index];
}

const TimelineFrame* GraphTimeline::GetFrameAtTick(uint64_t tick) const {
    for (const auto& frame : m_frames) {
        if (frame.tick == tick) return &frame;
    }
    return nullptr;
}

size_t GraphTimeline::CurrentIndex() const {
    return m_currentIndex;
}

bool GraphTimeline::SeekTo(size_t index) {
    if (index >= m_frames.size()) return false;
    m_currentIndex = index;
    return true;
}

bool GraphTimeline::StepForward() {
    if (m_frames.empty() || m_currentIndex >= m_frames.size() - 1) return false;
    ++m_currentIndex;
    return true;
}

bool GraphTimeline::StepBackward() {
    if (m_frames.empty() || m_currentIndex == 0) return false;
    --m_currentIndex;
    return true;
}

void GraphTimeline::SeekToBeginning() {
    m_currentIndex = 0;
}

void GraphTimeline::SeekToEnd() {
    if (!m_frames.empty()) {
        m_currentIndex = m_frames.size() - 1;
    }
}

const TimelineFrame* GraphTimeline::CurrentFrame() const {
    if (m_frames.empty()) return nullptr;
    return &m_frames[m_currentIndex];
}

GraphDiffResult GraphTimeline::DiffToNext() const {
    if (m_frames.empty() || m_currentIndex >= m_frames.size() - 1) {
        return {};
    }
    return ComputeGraphDiff(m_frames[m_currentIndex].snapshot,
                            m_frames[m_currentIndex + 1].snapshot);
}

GraphDiffResult GraphTimeline::DiffFromPrevious() const {
    if (m_frames.empty() || m_currentIndex == 0) {
        return {};
    }
    return ComputeGraphDiff(m_frames[m_currentIndex - 1].snapshot,
                            m_frames[m_currentIndex].snapshot);
}

void GraphTimeline::Clear() {
    m_frames.clear();
    m_currentIndex = 0;
}

std::pair<uint64_t, uint64_t> GraphTimeline::TickRange() const {
    if (m_frames.empty()) return {0, 0};
    return {m_frames.front().tick, m_frames.back().tick};
}

} // namespace atlas::graphvm
