#pragma once
#include <string>
#include <unordered_map>
#include <cstdint>
#include <functional>

namespace atlas::ai {

/// Cache entry for a deterministic LLM response.
/// Key = hash(prompt + seed + schema version).
struct LLMCacheEntry {
    uint64_t key = 0;
    std::string prompt;
    std::string response;
    uint32_t schemaVersion = 0;
    uint64_t seed = 0;
    uint64_t storedTick = 0;
};

/// Deterministic LLM response cache.
/// Seeded, hashed, versioned — ensures replay safety.
class LLMCache {
public:
    /// Compute a cache key from prompt, seed, and schema version.
    static uint64_t ComputeKey(const std::string& prompt, uint64_t seed, uint32_t schemaVersion);

    /// Store a response in the cache.
    void Store(const std::string& prompt, const std::string& response,
               uint64_t seed, uint32_t schemaVersion, uint64_t tick);

    /// Look up a cached response. Returns nullptr if not found.
    const LLMCacheEntry* Lookup(const std::string& prompt,
                                 uint64_t seed, uint32_t schemaVersion) const;

    /// Check if a cache entry exists.
    bool Has(const std::string& prompt, uint64_t seed, uint32_t schemaVersion) const;

    /// Evict entries stored before the given tick.
    void EvictBefore(uint64_t tick);

    /// Remove all cache entries.
    void Clear();

    size_t EntryCount() const { return m_entries.size(); }

private:
    std::unordered_map<uint64_t, LLMCacheEntry> m_entries;
};

} // namespace atlas::ai
