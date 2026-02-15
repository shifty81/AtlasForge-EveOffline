#include "../engine/graphvm/ReplayDiff.h"
#include <iostream>
#include <cassert>

using namespace atlas::graphvm;

void test_replay_diff_identical() {
    ReplayCapture a, b;
    GraphSnapshot snap;
    snap.nodes.push_back({1, "NodeA"});

    a.Record(10, "graph1", "execute", snap);
    b.Record(10, "graph1", "execute", snap);

    auto result = CompareReplays(a, b);
    assert(result.identical);
    assert(result.DifferenceCount() == 0);
    assert(result.hashA == result.hashB);

    std::cout << "[PASS] test_replay_diff_identical" << std::endl;
}

void test_replay_diff_event_count_mismatch() {
    ReplayCapture a, b;
    GraphSnapshot snap;

    a.Record(10, "graph1", "execute", snap);
    a.Record(20, "graph1", "execute", snap);
    b.Record(10, "graph1", "execute", snap);

    auto result = CompareReplays(a, b);
    assert(!result.identical);
    assert(result.DifferenceCount() >= 1);

    std::cout << "[PASS] test_replay_diff_event_count_mismatch" << std::endl;
}

void test_replay_diff_snapshot_mismatch() {
    ReplayCapture a, b;
    GraphSnapshot snapA, snapB;
    snapA.nodes.push_back({1, "NodeA"});
    snapB.nodes.push_back({1, "NodeA"});
    snapB.nodes.push_back({2, "NodeB"});  // extra node

    a.Record(10, "graph1", "execute", snapA);
    b.Record(10, "graph1", "execute", snapB);

    auto result = CompareReplays(a, b);
    assert(!result.identical);
    assert(result.DifferenceCount() == 1);
    assert(result.differences[0].snapshotMismatch);

    std::cout << "[PASS] test_replay_diff_snapshot_mismatch" << std::endl;
}

void test_replay_diff_event_type_mismatch() {
    ReplayCapture a, b;
    GraphSnapshot snap;

    a.Record(10, "graph1", "execute", snap);
    b.Record(10, "graph1", "propose", snap);

    auto result = CompareReplays(a, b);
    assert(!result.identical);
    assert(result.DifferenceCount() == 1);
    assert(result.differences[0].eventMismatch);

    std::cout << "[PASS] test_replay_diff_event_type_mismatch" << std::endl;
}

void test_replay_diff_empty() {
    ReplayCapture a, b;
    auto result = CompareReplays(a, b);
    assert(result.identical);
    assert(result.DifferenceCount() == 0);

    std::cout << "[PASS] test_replay_diff_empty" << std::endl;
}

void test_replay_diff_hash_values() {
    ReplayCapture a, b;
    GraphSnapshot snap;
    snap.nodes.push_back({1, "NodeA"});

    a.Record(10, "graph1", "execute", snap);
    b.Record(10, "graph1", "execute", snap);

    auto result = CompareReplays(a, b);
    assert(result.hashA != 0);
    assert(result.hashA == result.hashB);

    std::cout << "[PASS] test_replay_diff_hash_values" << std::endl;
}
