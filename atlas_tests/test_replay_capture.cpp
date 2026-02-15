#include "../engine/graphvm/ReplayCapture.h"
#include <iostream>
#include <cassert>

using namespace atlas::graphvm;

void test_replay_record() {
    ReplayCapture capture;
    GraphSnapshot snap;
    snap.nodes.push_back({1, "NodeA"});

    capture.Record(10, "graph1", "execute", snap);
    assert(capture.EventCount() == 1);

    const ReplayEvent* ev = capture.GetEvent(0);
    assert(ev != nullptr);
    assert(ev->tick == 10);
    assert(ev->graphId == "graph1");
    assert(ev->eventType == "execute");
    assert(ev->snapshot.nodes.size() == 1);

    std::cout << "[PASS] test_replay_record" << std::endl;
}

void test_replay_get_by_graph() {
    ReplayCapture capture;
    GraphSnapshot snap;

    capture.Record(10, "graph1", "execute", snap);
    capture.Record(11, "graph2", "execute", snap);
    capture.Record(12, "graph1", "propose", snap);

    auto g1 = capture.GetByGraph("graph1");
    assert(g1.size() == 2);

    auto g2 = capture.GetByGraph("graph2");
    assert(g2.size() == 1);

    auto g3 = capture.GetByGraph("missing");
    assert(g3.empty());

    std::cout << "[PASS] test_replay_get_by_graph" << std::endl;
}

void test_replay_get_by_tick() {
    ReplayCapture capture;
    GraphSnapshot snap;

    capture.Record(10, "g1", "execute", snap);
    capture.Record(10, "g2", "execute", snap);
    capture.Record(20, "g1", "execute", snap);

    auto t10 = capture.GetByTick(10);
    assert(t10.size() == 2);

    auto t20 = capture.GetByTick(20);
    assert(t20.size() == 1);

    auto t30 = capture.GetByTick(30);
    assert(t30.empty());

    std::cout << "[PASS] test_replay_get_by_tick" << std::endl;
}

void test_replay_tick_range() {
    ReplayCapture capture;
    GraphSnapshot snap;

    auto [min0, max0] = capture.TickRange();
    assert(min0 == 0 && max0 == 0);

    capture.Record(5, "g1", "execute", snap);
    capture.Record(15, "g2", "execute", snap);
    capture.Record(10, "g1", "propose", snap);

    auto [minTick, maxTick] = capture.TickRange();
    assert(minTick == 5);
    assert(maxTick == 15);

    std::cout << "[PASS] test_replay_tick_range" << std::endl;
}

void test_replay_get_by_tick_range() {
    ReplayCapture capture;
    GraphSnapshot snap;

    capture.Record(5, "g1", "execute", snap);
    capture.Record(10, "g2", "execute", snap);
    capture.Record(15, "g1", "propose", snap);
    capture.Record(20, "g1", "execute", snap);

    auto range = capture.GetByTickRange(10, 15);
    assert(range.size() == 2);

    std::cout << "[PASS] test_replay_get_by_tick_range" << std::endl;
}

void test_replay_deterministic_hash() {
    ReplayCapture capture1;
    ReplayCapture capture2;
    GraphSnapshot snap;
    snap.nodes.push_back({1, "NodeA"});
    snap.nodes.push_back({2, "NodeB"});

    capture1.Record(10, "graph1", "execute", snap);
    capture1.Record(20, "graph1", "execute", snap);

    capture2.Record(10, "graph1", "execute", snap);
    capture2.Record(20, "graph1", "execute", snap);

    assert(capture1.ComputeHash() == capture2.ComputeHash());

    // Different captures should produce different hashes
    ReplayCapture capture3;
    capture3.Record(10, "graph1", "execute", snap);
    assert(capture1.ComputeHash() != capture3.ComputeHash());

    std::cout << "[PASS] test_replay_deterministic_hash" << std::endl;
}

void test_replay_clear() {
    ReplayCapture capture;
    GraphSnapshot snap;

    capture.Record(10, "g1", "execute", snap);
    capture.Record(20, "g2", "execute", snap);
    assert(capture.EventCount() == 2);

    capture.Clear();
    assert(capture.EventCount() == 0);

    std::cout << "[PASS] test_replay_clear" << std::endl;
}

void test_replay_metadata() {
    ReplayCapture capture;
    GraphSnapshot snap;

    capture.Record(10, "g1", "execute", snap, "{\"score\": 42}");

    const ReplayEvent* ev = capture.GetEvent(0);
    assert(ev != nullptr);
    assert(ev->metadata == "{\"score\": 42}");

    std::cout << "[PASS] test_replay_metadata" << std::endl;
}
