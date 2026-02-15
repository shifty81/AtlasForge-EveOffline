#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <functional>
#include "GraphDiff.h"

namespace atlas::graphvm {

/// Result of a single determinism test run.
struct DeterminismTestResult {
    std::string testName;
    bool passed = false;
    uint64_t hashRun1 = 0;
    uint64_t hashRun2 = 0;
    std::string error;
};

/// A registered determinism test case.
struct DeterminismTestCase {
    std::string name;
    /// Function that produces a graph snapshot given a seed.
    /// Must be deterministic: same seed → same snapshot.
    std::function<GraphSnapshot(uint64_t seed)> producer;
};

/// CI Determinism Validator — verifies graph hash stability.
/// Runs registered graph producers twice with the same seed and
/// confirms the resulting snapshots are identical.
class DeterminismValidator {
public:
    /// Register a determinism test case.
    void Register(const std::string& name,
                  std::function<GraphSnapshot(uint64_t seed)> producer);

    /// Run all registered tests with the given seed.
    /// Each test is executed twice and outputs are compared.
    std::vector<DeterminismTestResult> RunAll(uint64_t seed) const;

    /// Run a single named test with the given seed.
    DeterminismTestResult RunOne(const std::string& name, uint64_t seed) const;

    /// Get the number of registered test cases.
    size_t TestCount() const;

    /// Clear all registered test cases.
    void Clear();

    /// Compute a hash for a graph snapshot (FNV-1a based).
    static uint64_t HashSnapshot(const GraphSnapshot& snapshot);

private:
    std::vector<DeterminismTestCase> m_tests;
};

} // namespace atlas::graphvm
