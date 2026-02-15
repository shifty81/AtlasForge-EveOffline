#include "ModSignalPolicy.h"
#include <algorithm>

namespace atlas::plugin {

void ModSignalPolicy::RegisterMod(const std::string& modName, const std::vector<std::string>& allowedNamespaces) {
    m_modNamespaces[modName] = allowedNamespaces;
}

void ModSignalPolicy::RegisterCoreNamespace(const std::string& ns) {
    m_coreNamespaces.insert(ns);
}

SignalAccessResult ModSignalPolicy::CheckAccess(const std::string& modName, const std::string& signalNamespace) const {
    auto it = m_modNamespaces.find(modName);
    if (it == m_modNamespaces.end()) return SignalAccessResult::UnregisteredMod;
    if (m_coreNamespaces.count(signalNamespace) > 0) return SignalAccessResult::DeniedCoreSignal;
    const auto& allowed = it->second;
    if (std::find(allowed.begin(), allowed.end(), signalNamespace) == allowed.end()) {
        return SignalAccessResult::DeniedNamespace;
    }
    return SignalAccessResult::Allowed;
}

bool ModSignalPolicy::IsCoreLocked(const std::string& ns) const {
    return m_coreNamespaces.count(ns) > 0;
}

std::vector<std::string> ModSignalPolicy::GetModNamespaces(const std::string& modName) const {
    auto it = m_modNamespaces.find(modName);
    if (it != m_modNamespaces.end()) return it->second;
    return {};
}

bool ModSignalPolicy::IsModRegistered(const std::string& modName) const {
    return m_modNamespaces.count(modName) > 0;
}

size_t ModSignalPolicy::ModCount() const {
    return m_modNamespaces.size();
}

size_t ModSignalPolicy::CoreNamespaceCount() const {
    return m_coreNamespaces.size();
}

void ModSignalPolicy::Clear() {
    m_modNamespaces.clear();
    m_coreNamespaces.clear();
}

} // namespace atlas::plugin
