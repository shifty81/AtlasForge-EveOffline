#include "../engine/plugin/ModOverlay.h"
#include <iostream>
#include <cassert>

void test_overlay_add_resolve() {
    atlas::plugin::ModOverlayResolver resolver;
    resolver.AddOverlay("ModA", "player.speed", "10.0", 1);
    assert(resolver.Resolve("player.speed") == "10.0");
    std::cout << "[PASS] test_overlay_add_resolve" << std::endl;
}

void test_overlay_highest_wins() {
    atlas::plugin::ModOverlayResolver resolver;
    resolver.AddOverlay("ModA", "player.speed", "10.0", 1);
    resolver.AddOverlay("ModB", "player.speed", "20.0", 5);
    resolver.AddOverlay("ModC", "player.speed", "15.0", 3);
    assert(resolver.Resolve("player.speed") == "20.0");
    std::cout << "[PASS] test_overlay_highest_wins" << std::endl;
}

void test_overlay_has_key() {
    atlas::plugin::ModOverlayResolver resolver;
    resolver.AddOverlay("ModA", "player.speed", "10.0", 1);
    assert(resolver.HasKey("player.speed"));
    assert(!resolver.HasKey("player.health"));
    std::cout << "[PASS] test_overlay_has_key" << std::endl;
}

void test_overlay_get_owner() {
    atlas::plugin::ModOverlayResolver resolver;
    resolver.AddOverlay("ModA", "player.speed", "10.0", 1);
    resolver.AddOverlay("ModB", "player.speed", "20.0", 5);
    assert(resolver.GetOwner("player.speed") == "ModB");
    assert(resolver.GetOwner("missing.key").empty());
    std::cout << "[PASS] test_overlay_get_owner" << std::endl;
}

void test_overlay_get_overlays_for_key() {
    atlas::plugin::ModOverlayResolver resolver;
    resolver.AddOverlay("ModB", "player.speed", "20.0", 5);
    resolver.AddOverlay("ModA", "player.speed", "10.0", 1);
    resolver.AddOverlay("ModC", "player.speed", "15.0", 3);

    auto overlays = resolver.GetOverlaysForKey("player.speed");
    assert(overlays.size() == 3);
    assert(overlays[0].modName == "ModA");
    assert(overlays[1].modName == "ModC");
    assert(overlays[2].modName == "ModB");
    std::cout << "[PASS] test_overlay_get_overlays_for_key" << std::endl;
}

void test_overlay_key_count() {
    atlas::plugin::ModOverlayResolver resolver;
    resolver.AddOverlay("ModA", "player.speed", "10.0", 1);
    resolver.AddOverlay("ModB", "player.speed", "20.0", 5);
    resolver.AddOverlay("ModA", "player.health", "100", 1);
    assert(resolver.KeyCount() == 2);
    assert(resolver.TotalOverlayCount() == 3);
    std::cout << "[PASS] test_overlay_key_count" << std::endl;
}

void test_overlay_clear() {
    atlas::plugin::ModOverlayResolver resolver;
    resolver.AddOverlay("ModA", "player.speed", "10.0", 1);
    assert(resolver.TotalOverlayCount() == 1);
    resolver.Clear();
    assert(resolver.TotalOverlayCount() == 0);
    assert(resolver.KeyCount() == 0);
    std::cout << "[PASS] test_overlay_clear" << std::endl;
}
