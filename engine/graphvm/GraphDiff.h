#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace atlas::graphvm {

/// Lightweight graph snapshot — a list of node IDs and edge pairs.
/// Any concrete graph can produce a snapshot for diff comparison.
struct GraphSnapshot {
    struct NodeEntry {
        uint32_t id;
        std::string type;   // node class name
    };
    struct EdgeEntry {
        uint32_t fromNode;
        uint16_t fromPort;
        uint32_t toNode;
        uint16_t toPort;
    };

    std::vector<NodeEntry> nodes;
    std::vector<EdgeEntry> edges;
};

enum class DiffAction : uint8_t {
    Added,
    Removed
};

struct NodeDiff {
    DiffAction action;
    uint32_t nodeId;
    std::string nodeType;
};

struct EdgeDiff {
    DiffAction action;
    GraphSnapshot::EdgeEntry edge;
};

struct GraphDiffResult {
    std::vector<NodeDiff> nodeDiffs;
    std::vector<EdgeDiff> edgeDiffs;

    bool HasChanges() const { return !nodeDiffs.empty() || !edgeDiffs.empty(); }
    size_t TotalChanges() const { return nodeDiffs.size() + edgeDiffs.size(); }
};

/// Compute the structural diff between two graph snapshots.
/// `before` is the baseline, `after` is the proposed state.
GraphDiffResult ComputeGraphDiff(const GraphSnapshot& before, const GraphSnapshot& after);

} // namespace atlas::graphvm
