#include "GraphDiff.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

namespace atlas::graphvm {

static uint64_t EdgeKey(const GraphSnapshot::EdgeEntry& e) {
    uint64_t key = static_cast<uint64_t>(e.fromNode) << 32;
    key |= static_cast<uint64_t>(e.fromPort) << 16;
    key ^= static_cast<uint64_t>(e.toNode) * 2654435761ULL;
    key ^= static_cast<uint64_t>(e.toPort);
    return key;
}

GraphDiffResult ComputeGraphDiff(const GraphSnapshot& before, const GraphSnapshot& after) {
    GraphDiffResult result;

    // --- Node diffs ---
    std::unordered_set<uint32_t> beforeNodeIDs;
    std::unordered_map<uint32_t, std::string> beforeNodeTypes;
    for (const auto& n : before.nodes) {
        beforeNodeIDs.insert(n.id);
        beforeNodeTypes[n.id] = n.type;
    }

    std::unordered_set<uint32_t> afterNodeIDs;
    for (const auto& n : after.nodes) {
        afterNodeIDs.insert(n.id);
    }

    // Removed nodes
    for (const auto& n : before.nodes) {
        if (afterNodeIDs.find(n.id) == afterNodeIDs.end()) {
            result.nodeDiffs.push_back({DiffAction::Removed, n.id, n.type});
        }
    }

    // Added nodes
    for (const auto& n : after.nodes) {
        if (beforeNodeIDs.find(n.id) == beforeNodeIDs.end()) {
            result.nodeDiffs.push_back({DiffAction::Added, n.id, n.type});
        }
    }

    // --- Edge diffs ---
    // Build sets of edge keys
    std::unordered_map<uint64_t, GraphSnapshot::EdgeEntry> beforeEdges;
    for (const auto& e : before.edges) {
        beforeEdges[EdgeKey(e)] = e;
    }

    std::unordered_map<uint64_t, GraphSnapshot::EdgeEntry> afterEdges;
    for (const auto& e : after.edges) {
        afterEdges[EdgeKey(e)] = e;
    }

    // Removed edges
    for (const auto& [key, edge] : beforeEdges) {
        if (afterEdges.find(key) == afterEdges.end()) {
            result.edgeDiffs.push_back({DiffAction::Removed, edge});
        }
    }

    // Added edges
    for (const auto& [key, edge] : afterEdges) {
        if (beforeEdges.find(key) == beforeEdges.end()) {
            result.edgeDiffs.push_back({DiffAction::Added, edge});
        }
    }

    return result;
}

} // namespace atlas::graphvm
