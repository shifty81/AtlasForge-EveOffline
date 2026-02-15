#include "../engine/ai/LLMCache.h"
#include <iostream>
#include <cassert>

using namespace atlas::ai;

void test_llm_cache_store_and_lookup() {
    LLMCache cache;
    cache.Store("test prompt", "test response", 42, 1, 100);

    const LLMCacheEntry* entry = cache.Lookup("test prompt", 42, 1);
    assert(entry != nullptr);
    assert(entry->prompt == "test prompt");
    assert(entry->response == "test response");
    assert(entry->seed == 42);
    assert(entry->schemaVersion == 1);
    assert(entry->storedTick == 100);

    std::cout << "[PASS] test_llm_cache_store_and_lookup" << std::endl;
}

void test_llm_cache_has() {
    LLMCache cache;
    assert(!cache.Has("test", 1, 1));

    cache.Store("test", "response", 1, 1, 50);
    assert(cache.Has("test", 1, 1));
    assert(!cache.Has("test", 2, 1));    // different seed
    assert(!cache.Has("test", 1, 2));    // different schema version
    assert(!cache.Has("other", 1, 1));   // different prompt

    std::cout << "[PASS] test_llm_cache_has" << std::endl;
}

void test_llm_cache_evict_before() {
    LLMCache cache;
    cache.Store("prompt1", "response1", 1, 1, 10);
    cache.Store("prompt2", "response2", 1, 1, 20);
    cache.Store("prompt3", "response3", 1, 1, 30);

    assert(cache.EntryCount() == 3);

    cache.EvictBefore(25);
    assert(cache.EntryCount() == 1);
    assert(!cache.Has("prompt1", 1, 1));
    assert(!cache.Has("prompt2", 1, 1));
    assert(cache.Has("prompt3", 1, 1));

    std::cout << "[PASS] test_llm_cache_evict_before" << std::endl;
}

void test_llm_cache_clear() {
    LLMCache cache;
    cache.Store("p1", "r1", 1, 1, 10);
    cache.Store("p2", "r2", 1, 1, 20);
    assert(cache.EntryCount() == 2);

    cache.Clear();
    assert(cache.EntryCount() == 0);

    std::cout << "[PASS] test_llm_cache_clear" << std::endl;
}

void test_llm_cache_deterministic_key() {
    // Same inputs should always produce the same key
    uint64_t key1 = LLMCache::ComputeKey("prompt", 42, 1);
    uint64_t key2 = LLMCache::ComputeKey("prompt", 42, 1);
    assert(key1 == key2);

    // Different inputs should produce different keys
    uint64_t key3 = LLMCache::ComputeKey("different", 42, 1);
    assert(key1 != key3);

    uint64_t key4 = LLMCache::ComputeKey("prompt", 99, 1);
    assert(key1 != key4);

    uint64_t key5 = LLMCache::ComputeKey("prompt", 42, 2);
    assert(key1 != key5);

    std::cout << "[PASS] test_llm_cache_deterministic_key" << std::endl;
}

void test_llm_cache_overwrite() {
    LLMCache cache;
    cache.Store("prompt", "old response", 1, 1, 10);
    cache.Store("prompt", "new response", 1, 1, 20);

    const LLMCacheEntry* entry = cache.Lookup("prompt", 1, 1);
    assert(entry != nullptr);
    assert(entry->response == "new response");
    assert(entry->storedTick == 20);
    assert(cache.EntryCount() == 1);

    std::cout << "[PASS] test_llm_cache_overwrite" << std::endl;
}
