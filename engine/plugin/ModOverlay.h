#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace atlas::plugin {

struct OverlayEntry {
    std::string modName;
    std::string key;
    std::string value;
    int loadOrder = 0;
};

class ModOverlayResolver {
public:
    void AddOverlay(const std::string& modName, const std::string& key,
                    const std::string& value, int loadOrder);

    std::string Resolve(const std::string& key) const;
    bool HasKey(const std::string& key) const;

    std::vector<OverlayEntry> GetOverlaysForKey(const std::string& key) const;

    std::string GetOwner(const std::string& key) const;

    size_t KeyCount() const;
    size_t TotalOverlayCount() const;
    void Clear();

private:
    std::vector<OverlayEntry> m_entries;
};

} // namespace atlas::plugin
