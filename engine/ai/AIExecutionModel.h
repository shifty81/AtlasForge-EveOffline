#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace atlas::ai {

enum class AIExecutionMode {
    Standalone,          // Full local AI execution (solo play)
    ServerAuthoritative, // Server runs AI, clients receive results
    ClientVisualization  // Client only displays AI state, no execution
};

struct AIExecutionConfig {
    AIExecutionMode mode = AIExecutionMode::Standalone;
    uint32_t maxConcurrentGraphs = 64;
    bool enableReplay = true;
    bool enablePrediction = false; // Client-side prediction for visual smoothness
};

struct AIExecutionResult {
    std::string graphID;
    uint32_t tick = 0;
    bool executed = false;
    std::string action;  // Result action from graph execution
    float confidence = 0.0f;
};

class AIExecutionModel {
public:
    void Init(const AIExecutionConfig& config);
    void Shutdown();

    AIExecutionMode Mode() const;
    bool IsAuthority() const; // True only in Standalone or ServerAuthoritative
    bool CanExecuteGraphs() const; // True if this instance runs AI graphs

    // Submit a graph for execution (rejected if not authority)
    bool Submit(const std::string& graphID, uint32_t tick);

    // Get results for a given tick
    std::vector<AIExecutionResult> GetResults(uint32_t tick) const;

    // Receive results from server (client-side only)
    void ReceiveResult(const AIExecutionResult& result);

    // Query
    size_t PendingCount() const;
    size_t ResultCount() const;
    void Clear();

private:
    AIExecutionConfig m_config;
    std::vector<std::string> m_pending;        // Pending graph IDs
    std::vector<AIExecutionResult> m_results;    // Completed results
};

}
