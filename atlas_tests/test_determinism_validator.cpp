#include "../engine/graphvm/DeterminismValidator.h"
#include <iostream>
#include <cassert>

using namespace atlas::graphvm;

void test_determinism_register() {
    DeterminismValidator validator;
    validator.Register("test1", [](uint64_t seed) {
        GraphSnapshot snap;
        snap.nodes.push_back({static_cast<uint32_t>(seed), "NodeA"});
        return snap;
    });
    assert(validator.TestCount() == 1);

    std::cout << "[PASS] test_determinism_register" << std::endl;
}

void test_determinism_pass() {
    DeterminismValidator validator;
    validator.Register("deterministic_graph", [](uint64_t seed) {
        GraphSnapshot snap;
        snap.nodes.push_back({static_cast<uint32_t>(seed % 100), "NodeA"});
        snap.nodes.push_back({static_cast<uint32_t>(seed % 100 + 1), "NodeB"});
        snap.edges.push_back({static_cast<uint32_t>(seed % 100), 0,
                              static_cast<uint32_t>(seed % 100 + 1), 0});
        return snap;
    });

    auto result = validator.RunOne("deterministic_graph", 42);
    assert(result.passed);
    assert(result.hashRun1 == result.hashRun2);
    assert(result.error.empty());

    std::cout << "[PASS] test_determinism_pass" << std::endl;
}

void test_determinism_run_all() {
    DeterminismValidator validator;

    validator.Register("test_a", [](uint64_t seed) {
        GraphSnapshot snap;
        snap.nodes.push_back({static_cast<uint32_t>(seed), "A"});
        return snap;
    });
    validator.Register("test_b", [](uint64_t seed) {
        GraphSnapshot snap;
        snap.nodes.push_back({static_cast<uint32_t>(seed + 1), "B"});
        return snap;
    });

    auto results = validator.RunAll(42);
    assert(results.size() == 2);
    assert(results[0].passed);
    assert(results[1].passed);

    std::cout << "[PASS] test_determinism_run_all" << std::endl;
}

void test_determinism_not_found() {
    DeterminismValidator validator;
    auto result = validator.RunOne("missing_test", 42);
    assert(!result.passed);
    assert(!result.error.empty());

    std::cout << "[PASS] test_determinism_not_found" << std::endl;
}

void test_determinism_hash_snapshot() {
    GraphSnapshot snap1;
    snap1.nodes.push_back({1, "NodeA"});
    snap1.nodes.push_back({2, "NodeB"});

    GraphSnapshot snap2;
    snap2.nodes.push_back({1, "NodeA"});
    snap2.nodes.push_back({2, "NodeB"});

    uint64_t hash1 = DeterminismValidator::HashSnapshot(snap1);
    uint64_t hash2 = DeterminismValidator::HashSnapshot(snap2);
    assert(hash1 == hash2);

    // Different snapshots should produce different hashes
    GraphSnapshot snap3;
    snap3.nodes.push_back({1, "NodeA"});
    snap3.nodes.push_back({3, "NodeC"});
    uint64_t hash3 = DeterminismValidator::HashSnapshot(snap3);
    assert(hash1 != hash3);

    std::cout << "[PASS] test_determinism_hash_snapshot" << std::endl;
}

void test_determinism_clear() {
    DeterminismValidator validator;
    validator.Register("test1", [](uint64_t) { return GraphSnapshot{}; });
    validator.Register("test2", [](uint64_t) { return GraphSnapshot{}; });
    assert(validator.TestCount() == 2);

    validator.Clear();
    assert(validator.TestCount() == 0);

    std::cout << "[PASS] test_determinism_clear" << std::endl;
}
