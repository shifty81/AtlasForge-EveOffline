#include "ModOverlay.h"
#include <algorithm>
#include <unordered_set>

namespace atlas::plugin {

void ModOverlayResolver::AddOverlay(const std::string& modName, const std::string& key,
                                    const std::string& value, int loadOrder) {
    m_entries.push_back({modName, key, value, loadOrder});
}

std::string ModOverlayResolver::Resolve(const std::string& key) const {
    const OverlayEntry* best = nullptr;
    for (const auto& e : m_entries) {
        if (e.key == key) {
            if (!best || e.loadOrder > best->loadOrder) {
                best = &e;
            }
        }
    }
    return best ? best->value : std::string();
}

bool ModOverlayResolver::HasKey(const std::string& key) const {
    for (const auto& e : m_entries) {
        if (e.key == key) return true;
    }
    return false;
}

std::vector<OverlayEntry> ModOverlayResolver::GetOverlaysForKey(const std::string& key) const {
    std::vector<OverlayEntry> result;
    for (const auto& e : m_entries) {
        if (e.key == key) result.push_back(e);
    }
    std::sort(result.begin(), result.end(),
              [](const OverlayEntry& a, const OverlayEntry& b) { return a.loadOrder < b.loadOrder; });
    return result;
}

std::string ModOverlayResolver::GetOwner(const std::string& key) const {
    const OverlayEntry* best = nullptr;
    for (const auto& e : m_entries) {
        if (e.key == key) {
            if (!best || e.loadOrder > best->loadOrder) {
                best = &e;
            }
        }
    }
    return best ? best->modName : std::string();
}

size_t ModOverlayResolver::KeyCount() const {
    std::unordered_set<std::string> keys;
    for (const auto& e : m_entries) {
        keys.insert(e.key);
    }
    return keys.size();
}

size_t ModOverlayResolver::TotalOverlayCount() const {
    return m_entries.size();
}

void ModOverlayResolver::Clear() {
    m_entries.clear();
}

} // namespace atlas::plugin
