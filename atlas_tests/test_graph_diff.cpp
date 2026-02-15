#include "../engine/graphvm/GraphDiff.h"
#include <iostream>
#include <cassert>

using namespace atlas::graphvm;

void test_graph_diff_empty() {
    GraphSnapshot before;
    GraphSnapshot after;
    auto result = ComputeGraphDiff(before, after);
    assert(!result.HasChanges());
    assert(result.TotalChanges() == 0);
    std::cout << "[PASS] test_graph_diff_empty" << std::endl;
}

void test_graph_diff_added_node() {
    GraphSnapshot before;
    before.nodes.push_back({1, "Noise"});

    GraphSnapshot after;
    after.nodes.push_back({1, "Noise"});
    after.nodes.push_back({2, "Blend"});

    auto result = ComputeGraphDiff(before, after);
    assert(result.HasChanges());
    assert(result.nodeDiffs.size() == 1);
    assert(result.nodeDiffs[0].action == DiffAction::Added);
    assert(result.nodeDiffs[0].nodeId == 2);
    assert(result.nodeDiffs[0].nodeType == "Blend");
    std::cout << "[PASS] test_graph_diff_added_node" << std::endl;
}

void test_graph_diff_removed_node() {
    GraphSnapshot before;
    before.nodes.push_back({1, "Noise"});
    before.nodes.push_back({2, "Blend"});

    GraphSnapshot after;
    after.nodes.push_back({1, "Noise"});

    auto result = ComputeGraphDiff(before, after);
    assert(result.HasChanges());
    assert(result.nodeDiffs.size() == 1);
    assert(result.nodeDiffs[0].action == DiffAction::Removed);
    assert(result.nodeDiffs[0].nodeId == 2);
    std::cout << "[PASS] test_graph_diff_removed_node" << std::endl;
}

void test_graph_diff_added_edge() {
    GraphSnapshot before;
    before.nodes.push_back({1, "A"});
    before.nodes.push_back({2, "B"});

    GraphSnapshot after;
    after.nodes.push_back({1, "A"});
    after.nodes.push_back({2, "B"});
    after.edges.push_back({1, 0, 2, 0});

    auto result = ComputeGraphDiff(before, after);
    assert(result.HasChanges());
    assert(result.edgeDiffs.size() == 1);
    assert(result.edgeDiffs[0].action == DiffAction::Added);
    assert(result.edgeDiffs[0].edge.fromNode == 1);
    assert(result.edgeDiffs[0].edge.toNode == 2);
    std::cout << "[PASS] test_graph_diff_added_edge" << std::endl;
}

void test_graph_diff_removed_edge() {
    GraphSnapshot before;
    before.nodes.push_back({1, "A"});
    before.nodes.push_back({2, "B"});
    before.edges.push_back({1, 0, 2, 0});

    GraphSnapshot after;
    after.nodes.push_back({1, "A"});
    after.nodes.push_back({2, "B"});

    auto result = ComputeGraphDiff(before, after);
    assert(result.HasChanges());
    assert(result.edgeDiffs.size() == 1);
    assert(result.edgeDiffs[0].action == DiffAction::Removed);
    std::cout << "[PASS] test_graph_diff_removed_edge" << std::endl;
}

void test_graph_diff_no_changes() {
    GraphSnapshot before;
    before.nodes.push_back({1, "A"});
    before.nodes.push_back({2, "B"});
    before.edges.push_back({1, 0, 2, 0});

    GraphSnapshot after;
    after.nodes.push_back({1, "A"});
    after.nodes.push_back({2, "B"});
    after.edges.push_back({1, 0, 2, 0});

    auto result = ComputeGraphDiff(before, after);
    assert(!result.HasChanges());
    std::cout << "[PASS] test_graph_diff_no_changes" << std::endl;
}

void test_graph_diff_complex() {
    GraphSnapshot before;
    before.nodes.push_back({1, "Noise"});
    before.nodes.push_back({2, "Blend"});
    before.nodes.push_back({3, "Clamp"});
    before.edges.push_back({1, 0, 2, 0});
    before.edges.push_back({2, 0, 3, 0});

    GraphSnapshot after;
    after.nodes.push_back({1, "Noise"});
    after.nodes.push_back({3, "Clamp"});
    after.nodes.push_back({4, "Output"});
    after.edges.push_back({1, 0, 3, 0});  // new direct edge
    after.edges.push_back({3, 0, 4, 0});  // new edge

    auto result = ComputeGraphDiff(before, after);
    assert(result.HasChanges());

    // Should have: removed node 2, added node 4
    size_t addedNodes = 0, removedNodes = 0;
    for (const auto& d : result.nodeDiffs) {
        if (d.action == DiffAction::Added) addedNodes++;
        if (d.action == DiffAction::Removed) removedNodes++;
    }
    assert(addedNodes == 1);
    assert(removedNodes == 1);

    // Should have edge changes
    assert(!result.edgeDiffs.empty());
    std::cout << "[PASS] test_graph_diff_complex" << std::endl;
}
