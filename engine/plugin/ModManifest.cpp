#include "ModManifest.h"
#include <algorithm>

namespace atlas::plugin {

ModDescriptor ModManifestParser::Parse(const std::string& name, const std::string& version,
                                       const std::string& author, int loadOrder) {
    ModDescriptor desc;
    desc.name = name;
    desc.version = version;
    desc.author = author;
    desc.loadOrder = loadOrder;
    return desc;
}

ModLoadResult ModManifestParser::Validate(const ModDescriptor& descriptor) {
    if (descriptor.name.empty()) return ModLoadResult::EmptyName;
    if (descriptor.version.empty()) return ModLoadResult::EmptyVersion;
    return ModLoadResult::Success;
}

ModLoadResult ModRegistry::Register(const ModDescriptor& descriptor) {
    ModLoadResult result = ModManifestParser::Validate(descriptor);
    if (result != ModLoadResult::Success) return result;
    if (Find(descriptor.name) != nullptr) return ModLoadResult::DuplicateName;
    m_mods.push_back(descriptor);
    return ModLoadResult::Success;
}

bool ModRegistry::Unregister(const std::string& name) {
    auto it = std::remove_if(m_mods.begin(), m_mods.end(),
                             [&name](const ModDescriptor& d) { return d.name == name; });
    if (it == m_mods.end()) return false;
    m_mods.erase(it, m_mods.end());
    return true;
}

const ModDescriptor* ModRegistry::Find(const std::string& name) const {
    for (const auto& m : m_mods) {
        if (m.name == name) return &m;
    }
    return nullptr;
}

std::vector<ModDescriptor> ModRegistry::GetAll() const {
    return m_mods;
}

std::vector<ModDescriptor> ModRegistry::GetSorted() const {
    std::vector<ModDescriptor> sorted = m_mods;
    std::sort(sorted.begin(), sorted.end(),
              [](const ModDescriptor& a, const ModDescriptor& b) { return a.loadOrder < b.loadOrder; });
    return sorted;
}

size_t ModRegistry::ModCount() const {
    return m_mods.size();
}

bool ModRegistry::AreDependenciesMet(const std::string& modName) const {
    const ModDescriptor* mod = Find(modName);
    if (!mod) return false;
    for (const auto& dep : mod->dependencies) {
        if (Find(dep.modName) == nullptr) return false;
    }
    return true;
}

void ModRegistry::Clear() {
    m_mods.clear();
}

} // namespace atlas::plugin
