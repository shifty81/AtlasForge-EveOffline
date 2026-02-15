#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

namespace atlas::ai {

struct AIVisualState {
    uint32_t entityID = 0;
    std::string currentAction;
    float confidence = 0.0f;
    uint32_t lastUpdateTick = 0;
    std::string graphID;
};

class AIVisualization {
public:
    // Update visual state from server data
    void UpdateEntity(uint32_t entityID, const std::string& action, float confidence,
                      uint32_t tick, const std::string& graphID = "");

    // Query visual state
    const AIVisualState* GetEntityState(uint32_t entityID) const;
    bool HasEntity(uint32_t entityID) const;
    std::vector<uint32_t> GetActiveEntities() const;

    // Stale detection — entities not updated for N ticks
    std::vector<uint32_t> GetStaleEntities(uint32_t currentTick, uint32_t threshold) const;
    void PurgeStale(uint32_t currentTick, uint32_t threshold);

    size_t EntityCount() const;
    void Clear();

private:
    std::unordered_map<uint32_t, AIVisualState> m_states;
};

}
