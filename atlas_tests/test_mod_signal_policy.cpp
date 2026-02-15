#include "../engine/plugin/ModSignalPolicy.h"
#include <iostream>
#include <cassert>

void test_signal_policy_allowed() {
    atlas::plugin::ModSignalPolicy policy;
    policy.RegisterMod("TestMod", {"mod.test", "mod.custom"});
    auto result = policy.CheckAccess("TestMod", "mod.test");
    assert(result == atlas::plugin::SignalAccessResult::Allowed);
    std::cout << "[PASS] test_signal_policy_allowed" << std::endl;
}

void test_signal_policy_denied_namespace() {
    atlas::plugin::ModSignalPolicy policy;
    policy.RegisterMod("TestMod", {"mod.test"});
    auto result = policy.CheckAccess("TestMod", "mod.other");
    assert(result == atlas::plugin::SignalAccessResult::DeniedNamespace);
    std::cout << "[PASS] test_signal_policy_denied_namespace" << std::endl;
}

void test_signal_policy_denied_core() {
    atlas::plugin::ModSignalPolicy policy;
    policy.RegisterMod("TestMod", {"engine.core"});
    policy.RegisterCoreNamespace("engine.core");
    auto result = policy.CheckAccess("TestMod", "engine.core");
    assert(result == atlas::plugin::SignalAccessResult::DeniedCoreSignal);
    std::cout << "[PASS] test_signal_policy_denied_core" << std::endl;
}

void test_signal_policy_unregistered() {
    atlas::plugin::ModSignalPolicy policy;
    auto result = policy.CheckAccess("Unknown", "mod.test");
    assert(result == atlas::plugin::SignalAccessResult::UnregisteredMod);
    std::cout << "[PASS] test_signal_policy_unregistered" << std::endl;
}

void test_signal_policy_core_locked() {
    atlas::plugin::ModSignalPolicy policy;
    policy.RegisterCoreNamespace("engine.core");
    assert(policy.IsCoreLocked("engine.core"));
    assert(!policy.IsCoreLocked("mod.test"));
    std::cout << "[PASS] test_signal_policy_core_locked" << std::endl;
}

void test_signal_policy_get_namespaces() {
    atlas::plugin::ModSignalPolicy policy;
    policy.RegisterMod("TestMod", {"mod.test", "mod.custom"});
    auto ns = policy.GetModNamespaces("TestMod");
    assert(ns.size() == 2);
    auto empty = policy.GetModNamespaces("Unknown");
    assert(empty.empty());
    std::cout << "[PASS] test_signal_policy_get_namespaces" << std::endl;
}

void test_signal_policy_clear() {
    atlas::plugin::ModSignalPolicy policy;
    policy.RegisterMod("TestMod", {"mod.test"});
    policy.RegisterCoreNamespace("engine.core");
    assert(policy.ModCount() == 1);
    assert(policy.CoreNamespaceCount() == 1);
    policy.Clear();
    assert(policy.ModCount() == 0);
    assert(policy.CoreNamespaceCount() == 0);
    assert(!policy.IsModRegistered("TestMod"));
    std::cout << "[PASS] test_signal_policy_clear" << std::endl;
}
