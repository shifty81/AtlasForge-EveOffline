#pragma once
#include <string>
#include <vector>

namespace atlas::plugin {

struct ModDependency {
    std::string modName;
    std::string minVersion;
};

struct ModDescriptor {
    std::string name;
    std::string version;
    std::string author;
    std::string description;
    int loadOrder = 0;
    std::vector<std::string> signalNamespaces;
    std::vector<ModDependency> dependencies;
};

enum class ModLoadResult { Success, EmptyName, EmptyVersion, DuplicateName, DependencyMissing };

class ModManifestParser {
public:
    static ModDescriptor Parse(const std::string& name, const std::string& version,
                               const std::string& author = "", int loadOrder = 0);

    static ModLoadResult Validate(const ModDescriptor& descriptor);
};

class ModRegistry {
public:
    ModLoadResult Register(const ModDescriptor& descriptor);
    bool Unregister(const std::string& name);
    const ModDescriptor* Find(const std::string& name) const;

    std::vector<ModDescriptor> GetAll() const;
    std::vector<ModDescriptor> GetSorted() const;
    size_t ModCount() const;

    bool AreDependenciesMet(const std::string& modName) const;

    void Clear();

private:
    std::vector<ModDescriptor> m_mods;
};

} // namespace atlas::plugin
