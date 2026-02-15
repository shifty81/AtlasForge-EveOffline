#include "PluginPermission.h"
#include <algorithm>

namespace atlas::plugin {

void PermissionValidator::RegisterManifest(const PermissionManifest& manifest) {
    if (manifest.pluginName.empty()) return;
    for (const auto& m : m_manifests) {
        if (m.pluginName == manifest.pluginName) return;
    }
    m_manifests.push_back(manifest);
}

bool PermissionValidator::HasPermission(const std::string& pluginName, Permission perm) const {
    for (const auto& m : m_manifests) {
        if (m.pluginName == pluginName) {
            return std::find(m.granted.begin(), m.granted.end(), perm) != m.granted.end();
        }
    }
    return false;
}

std::vector<Permission> PermissionValidator::GetPermissions(const std::string& pluginName) const {
    for (const auto& m : m_manifests) {
        if (m.pluginName == pluginName) return m.granted;
    }
    return {};
}

bool PermissionValidator::ValidateManifest(const PermissionManifest& manifest,
                                           const std::vector<Permission>& maxAllowed) const {
    for (const auto& perm : manifest.granted) {
        if (std::find(maxAllowed.begin(), maxAllowed.end(), perm) == maxAllowed.end()) {
            return false;
        }
    }
    return true;
}

size_t PermissionValidator::ManifestCount() const {
    return m_manifests.size();
}

void PermissionValidator::Clear() {
    m_manifests.clear();
}

} // namespace atlas::plugin
