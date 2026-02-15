#include "AIVisualization.h"

namespace atlas::ai {

void AIVisualization::UpdateEntity(uint32_t entityID, const std::string& action,
                                   float confidence, uint32_t tick,
                                   const std::string& graphID) {
    AIVisualState state;
    state.entityID = entityID;
    state.currentAction = action;
    state.confidence = confidence;
    state.lastUpdateTick = tick;
    state.graphID = graphID;
    m_states[entityID] = state;
}

const AIVisualState* AIVisualization::GetEntityState(uint32_t entityID) const {
    auto it = m_states.find(entityID);
    if (it == m_states.end()) return nullptr;
    return &it->second;
}

bool AIVisualization::HasEntity(uint32_t entityID) const {
    return m_states.count(entityID) > 0;
}

std::vector<uint32_t> AIVisualization::GetActiveEntities() const {
    std::vector<uint32_t> ids;
    for (const auto& pair : m_states) {
        ids.push_back(pair.first);
    }
    return ids;
}

std::vector<uint32_t> AIVisualization::GetStaleEntities(uint32_t currentTick,
                                                         uint32_t threshold) const {
    std::vector<uint32_t> stale;
    for (const auto& pair : m_states) {
        if (currentTick > pair.second.lastUpdateTick &&
            currentTick - pair.second.lastUpdateTick > threshold) {
            stale.push_back(pair.first);
        }
    }
    return stale;
}

void AIVisualization::PurgeStale(uint32_t currentTick, uint32_t threshold) {
    auto it = m_states.begin();
    while (it != m_states.end()) {
        if (currentTick > it->second.lastUpdateTick &&
            currentTick - it->second.lastUpdateTick > threshold) {
            it = m_states.erase(it);
        } else {
            ++it;
        }
    }
}

size_t AIVisualization::EntityCount() const {
    return m_states.size();
}

void AIVisualization::Clear() {
    m_states.clear();
}

}
