#include "../engine/plugin/PluginPermission.h"
#include <iostream>
#include <cassert>

void test_perm_register() {
    atlas::plugin::PermissionValidator validator;
    atlas::plugin::PermissionManifest manifest;
    manifest.pluginName = "TestPlugin";
    manifest.granted = {atlas::plugin::Permission::ReadSignals, atlas::plugin::Permission::ReadECS};
    validator.RegisterManifest(manifest);
    assert(validator.ManifestCount() == 1);
    std::cout << "[PASS] test_perm_register" << std::endl;
}

void test_perm_has_permission() {
    atlas::plugin::PermissionValidator validator;
    atlas::plugin::PermissionManifest manifest;
    manifest.pluginName = "TestPlugin";
    manifest.granted = {atlas::plugin::Permission::ReadSignals, atlas::plugin::Permission::WriteECS};
    validator.RegisterManifest(manifest);
    assert(validator.HasPermission("TestPlugin", atlas::plugin::Permission::ReadSignals));
    assert(validator.HasPermission("TestPlugin", atlas::plugin::Permission::WriteECS));
    std::cout << "[PASS] test_perm_has_permission" << std::endl;
}

void test_perm_missing_permission() {
    atlas::plugin::PermissionValidator validator;
    atlas::plugin::PermissionManifest manifest;
    manifest.pluginName = "TestPlugin";
    manifest.granted = {atlas::plugin::Permission::ReadSignals};
    validator.RegisterManifest(manifest);
    assert(!validator.HasPermission("TestPlugin", atlas::plugin::Permission::NetworkSend));
    assert(!validator.HasPermission("Unknown", atlas::plugin::Permission::ReadSignals));
    std::cout << "[PASS] test_perm_missing_permission" << std::endl;
}

void test_perm_validate_manifest() {
    atlas::plugin::PermissionValidator validator;
    atlas::plugin::PermissionManifest manifest;
    manifest.pluginName = "TestPlugin";
    manifest.granted = {atlas::plugin::Permission::ReadSignals, atlas::plugin::Permission::ReadECS};

    std::vector<atlas::plugin::Permission> maxAllowed = {
        atlas::plugin::Permission::ReadSignals,
        atlas::plugin::Permission::ReadECS,
        atlas::plugin::Permission::WriteECS
    };
    assert(validator.ValidateManifest(manifest, maxAllowed));
    std::cout << "[PASS] test_perm_validate_manifest" << std::endl;
}

void test_perm_validate_exceeds() {
    atlas::plugin::PermissionValidator validator;
    atlas::plugin::PermissionManifest manifest;
    manifest.pluginName = "TestPlugin";
    manifest.granted = {atlas::plugin::Permission::ReadSignals, atlas::plugin::Permission::NetworkSend};

    std::vector<atlas::plugin::Permission> maxAllowed = {
        atlas::plugin::Permission::ReadSignals,
        atlas::plugin::Permission::ReadECS
    };
    assert(!validator.ValidateManifest(manifest, maxAllowed));
    std::cout << "[PASS] test_perm_validate_exceeds" << std::endl;
}

void test_perm_get_permissions() {
    atlas::plugin::PermissionValidator validator;
    atlas::plugin::PermissionManifest manifest;
    manifest.pluginName = "TestPlugin";
    manifest.granted = {atlas::plugin::Permission::ReadSignals, atlas::plugin::Permission::AssetRead};
    validator.RegisterManifest(manifest);

    auto perms = validator.GetPermissions("TestPlugin");
    assert(perms.size() == 2);
    auto empty = validator.GetPermissions("Unknown");
    assert(empty.empty());
    std::cout << "[PASS] test_perm_get_permissions" << std::endl;
}

void test_perm_clear() {
    atlas::plugin::PermissionValidator validator;
    atlas::plugin::PermissionManifest manifest;
    manifest.pluginName = "TestPlugin";
    manifest.granted = {atlas::plugin::Permission::ReadSignals};
    validator.RegisterManifest(manifest);
    assert(validator.ManifestCount() == 1);
    validator.Clear();
    assert(validator.ManifestCount() == 0);
    std::cout << "[PASS] test_perm_clear" << std::endl;
}
