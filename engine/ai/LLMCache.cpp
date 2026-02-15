#include "LLMCache.h"

namespace atlas::ai {

uint64_t LLMCache::ComputeKey(const std::string& prompt, uint64_t seed, uint32_t schemaVersion) {
    // FNV-1a hash for deterministic cache lookup
    uint64_t hash = 14695981039346656037ULL;
    for (char c : prompt) {
        hash ^= static_cast<uint64_t>(static_cast<unsigned char>(c));
        hash *= 1099511628211ULL;
    }
    // Mix in seed
    hash ^= seed;
    hash *= 1099511628211ULL;
    // Mix in schema version
    hash ^= static_cast<uint64_t>(schemaVersion);
    hash *= 1099511628211ULL;
    return hash;
}

void LLMCache::Store(const std::string& prompt, const std::string& response,
                      uint64_t seed, uint32_t schemaVersion, uint64_t tick) {
    uint64_t key = ComputeKey(prompt, seed, schemaVersion);
    m_entries[key] = {key, prompt, response, schemaVersion, seed, tick};
}

const LLMCacheEntry* LLMCache::Lookup(const std::string& prompt,
                                        uint64_t seed, uint32_t schemaVersion) const {
    uint64_t key = ComputeKey(prompt, seed, schemaVersion);
    auto it = m_entries.find(key);
    if (it == m_entries.end()) return nullptr;
    return &it->second;
}

bool LLMCache::Has(const std::string& prompt, uint64_t seed, uint32_t schemaVersion) const {
    return Lookup(prompt, seed, schemaVersion) != nullptr;
}

void LLMCache::EvictBefore(uint64_t tick) {
    for (auto it = m_entries.begin(); it != m_entries.end(); ) {
        if (it->second.storedTick < tick) {
            it = m_entries.erase(it);
        } else {
            ++it;
        }
    }
}

void LLMCache::Clear() {
    m_entries.clear();
}

} // namespace atlas::ai
