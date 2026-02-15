#include "AIExecutionModel.h"

namespace atlas::ai {

void AIExecutionModel::Init(const AIExecutionConfig& config) {
    m_config = config;
    m_pending.clear();
    m_results.clear();
}

void AIExecutionModel::Shutdown() {
    m_pending.clear();
    m_results.clear();
    m_config = AIExecutionConfig();
}

AIExecutionMode AIExecutionModel::Mode() const {
    return m_config.mode;
}

bool AIExecutionModel::IsAuthority() const {
    return m_config.mode == AIExecutionMode::Standalone ||
           m_config.mode == AIExecutionMode::ServerAuthoritative;
}

bool AIExecutionModel::CanExecuteGraphs() const {
    return IsAuthority();
}

bool AIExecutionModel::Submit(const std::string& graphID, uint32_t tick) {
    if (!IsAuthority()) return false;

    m_pending.push_back(graphID);

    AIExecutionResult result;
    result.graphID = graphID;
    result.tick = tick;
    result.executed = true;
    result.action = "idle";
    result.confidence = 1.0f;
    m_results.push_back(result);

    return true;
}

std::vector<AIExecutionResult> AIExecutionModel::GetResults(uint32_t tick) const {
    std::vector<AIExecutionResult> filtered;
    for (const auto& r : m_results) {
        if (r.tick == tick) {
            filtered.push_back(r);
        }
    }
    return filtered;
}

void AIExecutionModel::ReceiveResult(const AIExecutionResult& result) {
    if (m_config.mode != AIExecutionMode::ClientVisualization) return;
    m_results.push_back(result);
}

size_t AIExecutionModel::PendingCount() const {
    return m_pending.size();
}

size_t AIExecutionModel::ResultCount() const {
    return m_results.size();
}

void AIExecutionModel::Clear() {
    m_pending.clear();
    m_results.clear();
}

}
