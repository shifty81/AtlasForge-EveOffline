#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace atlas::plugin {

enum class SignalAccessResult { Allowed, DeniedNamespace, DeniedCoreSignal, UnregisteredMod };

class ModSignalPolicy {
public:
    void RegisterMod(const std::string& modName, const std::vector<std::string>& allowedNamespaces);

    void RegisterCoreNamespace(const std::string& ns);

    SignalAccessResult CheckAccess(const std::string& modName, const std::string& signalNamespace) const;

    bool IsCoreLocked(const std::string& ns) const;
    std::vector<std::string> GetModNamespaces(const std::string& modName) const;
    bool IsModRegistered(const std::string& modName) const;

    size_t ModCount() const;
    size_t CoreNamespaceCount() const;
    void Clear();

private:
    std::unordered_map<std::string, std::vector<std::string>> m_modNamespaces;
    std::unordered_set<std::string> m_coreNamespaces;
};

} // namespace atlas::plugin
