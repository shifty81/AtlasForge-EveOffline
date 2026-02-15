#pragma once
#include <string>
#include <vector>

namespace atlas::plugin {

enum class Permission {
    ReadSignals,
    WriteSignals,
    ReadECS,
    WriteECS,
    NetworkSend,
    AssetRead,
    AssetWrite,
    GraphExecute
};

struct PermissionManifest {
    std::string pluginName;
    std::vector<Permission> granted;
};

class PermissionValidator {
public:
    void RegisterManifest(const PermissionManifest& manifest);

    bool HasPermission(const std::string& pluginName, Permission perm) const;

    std::vector<Permission> GetPermissions(const std::string& pluginName) const;

    bool ValidateManifest(const PermissionManifest& manifest,
                          const std::vector<Permission>& maxAllowed) const;

    size_t ManifestCount() const;
    void Clear();

private:
    std::vector<PermissionManifest> m_manifests;
};

} // namespace atlas::plugin
