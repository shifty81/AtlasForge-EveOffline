#include "DeterminismValidator.h"

namespace atlas::graphvm {

void DeterminismValidator::Register(const std::string& name,
                                     std::function<GraphSnapshot(uint64_t seed)> producer) {
    m_tests.push_back({name, std::move(producer)});
}

std::vector<DeterminismTestResult> DeterminismValidator::RunAll(uint64_t seed) const {
    std::vector<DeterminismTestResult> results;
    results.reserve(m_tests.size());
    for (const auto& test : m_tests) {
        results.push_back(RunOne(test.name, seed));
    }
    return results;
}

DeterminismTestResult DeterminismValidator::RunOne(const std::string& name, uint64_t seed) const {
    DeterminismTestResult result;
    result.testName = name;

    const DeterminismTestCase* testCase = nullptr;
    for (const auto& t : m_tests) {
        if (t.name == name) {
            testCase = &t;
            break;
        }
    }

    if (!testCase) {
        result.passed = false;
        result.error = "Test not found: " + name;
        return result;
    }

    // Run the producer twice with the same seed
    GraphSnapshot snap1 = testCase->producer(seed);
    GraphSnapshot snap2 = testCase->producer(seed);

    result.hashRun1 = HashSnapshot(snap1);
    result.hashRun2 = HashSnapshot(snap2);
    result.passed = (result.hashRun1 == result.hashRun2);

    if (!result.passed) {
        result.error = "Hash mismatch: run1=" + std::to_string(result.hashRun1) +
                       " run2=" + std::to_string(result.hashRun2);
    }

    return result;
}

size_t DeterminismValidator::TestCount() const {
    return m_tests.size();
}

void DeterminismValidator::Clear() {
    m_tests.clear();
}

uint64_t DeterminismValidator::HashSnapshot(const GraphSnapshot& snapshot) {
    // FNV-1a hash for deterministic snapshot hashing
    uint64_t hash = 14695981039346656037ULL;

    // Hash node count
    hash ^= static_cast<uint64_t>(snapshot.nodes.size());
    hash *= 1099511628211ULL;

    // Hash each node's ID and type
    for (const auto& n : snapshot.nodes) {
        hash ^= static_cast<uint64_t>(n.id);
        hash *= 1099511628211ULL;
        for (char c : n.type) {
            hash ^= static_cast<uint64_t>(static_cast<unsigned char>(c));
            hash *= 1099511628211ULL;
        }
    }

    // Hash edge count
    hash ^= static_cast<uint64_t>(snapshot.edges.size());
    hash *= 1099511628211ULL;

    // Hash each edge
    for (const auto& e : snapshot.edges) {
        hash ^= static_cast<uint64_t>(e.fromNode);
        hash *= 1099511628211ULL;
        hash ^= static_cast<uint64_t>(e.fromPort);
        hash *= 1099511628211ULL;
        hash ^= static_cast<uint64_t>(e.toNode);
        hash *= 1099511628211ULL;
        hash ^= static_cast<uint64_t>(e.toPort);
        hash *= 1099511628211ULL;
    }

    return hash;
}

} // namespace atlas::graphvm
