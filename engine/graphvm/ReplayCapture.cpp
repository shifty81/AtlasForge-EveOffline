#include "ReplayCapture.h"

namespace atlas::graphvm {

void ReplayCapture::Record(uint64_t tick, const std::string& graphId,
                            const std::string& eventType,
                            const GraphSnapshot& snapshot,
                            const std::string& metadata) {
    ReplayEvent event;
    event.tick = tick;
    event.graphId = graphId;
    event.eventType = eventType;
    event.snapshot = snapshot;
    event.metadata = metadata;
    m_events.push_back(std::move(event));
}

size_t ReplayCapture::EventCount() const {
    return m_events.size();
}

const ReplayEvent* ReplayCapture::GetEvent(size_t index) const {
    if (index >= m_events.size()) return nullptr;
    return &m_events[index];
}

std::vector<const ReplayEvent*> ReplayCapture::GetByGraph(const std::string& graphId) const {
    std::vector<const ReplayEvent*> result;
    for (const auto& e : m_events) {
        if (e.graphId == graphId) result.push_back(&e);
    }
    return result;
}

std::vector<const ReplayEvent*> ReplayCapture::GetByTick(uint64_t tick) const {
    std::vector<const ReplayEvent*> result;
    for (const auto& e : m_events) {
        if (e.tick == tick) result.push_back(&e);
    }
    return result;
}

std::vector<const ReplayEvent*> ReplayCapture::GetByTickRange(uint64_t startTick, uint64_t endTick) const {
    std::vector<const ReplayEvent*> result;
    for (const auto& e : m_events) {
        if (e.tick >= startTick && e.tick <= endTick) result.push_back(&e);
    }
    return result;
}

std::pair<uint64_t, uint64_t> ReplayCapture::TickRange() const {
    if (m_events.empty()) return {0, 0};
    uint64_t minTick = m_events.front().tick;
    uint64_t maxTick = m_events.front().tick;
    for (const auto& e : m_events) {
        if (e.tick < minTick) minTick = e.tick;
        if (e.tick > maxTick) maxTick = e.tick;
    }
    return {minTick, maxTick};
}

uint64_t ReplayCapture::ComputeHash() const {
    // FNV-1a hash over all event data for determinism verification
    uint64_t hash = 14695981039346656037ULL;
    for (const auto& e : m_events) {
        // Hash tick
        hash ^= e.tick;
        hash *= 1099511628211ULL;
        // Hash graphId
        for (char c : e.graphId) {
            hash ^= static_cast<uint64_t>(static_cast<unsigned char>(c));
            hash *= 1099511628211ULL;
        }
        // Hash eventType
        for (char c : e.eventType) {
            hash ^= static_cast<uint64_t>(static_cast<unsigned char>(c));
            hash *= 1099511628211ULL;
        }
        // Hash node count and IDs
        hash ^= static_cast<uint64_t>(e.snapshot.nodes.size());
        hash *= 1099511628211ULL;
        for (const auto& n : e.snapshot.nodes) {
            hash ^= static_cast<uint64_t>(n.id);
            hash *= 1099511628211ULL;
        }
        // Hash edge count
        hash ^= static_cast<uint64_t>(e.snapshot.edges.size());
        hash *= 1099511628211ULL;
    }
    return hash;
}

void ReplayCapture::Clear() {
    m_events.clear();
}

} // namespace atlas::graphvm
