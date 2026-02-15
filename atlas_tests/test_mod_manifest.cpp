#include "../engine/plugin/ModManifest.h"
#include <iostream>
#include <cassert>

void test_mod_parse() {
    auto desc = atlas::plugin::ModManifestParser::Parse("TestMod", "1.0.0", "Author", 5);
    assert(desc.name == "TestMod");
    assert(desc.version == "1.0.0");
    assert(desc.author == "Author");
    assert(desc.loadOrder == 5);
    std::cout << "[PASS] test_mod_parse" << std::endl;
}

void test_mod_validate_valid() {
    auto desc = atlas::plugin::ModManifestParser::Parse("TestMod", "1.0.0");
    auto result = atlas::plugin::ModManifestParser::Validate(desc);
    assert(result == atlas::plugin::ModLoadResult::Success);
    std::cout << "[PASS] test_mod_validate_valid" << std::endl;
}

void test_mod_validate_empty_name() {
    auto desc = atlas::plugin::ModManifestParser::Parse("", "1.0.0");
    auto result = atlas::plugin::ModManifestParser::Validate(desc);
    assert(result == atlas::plugin::ModLoadResult::EmptyName);
    std::cout << "[PASS] test_mod_validate_empty_name" << std::endl;
}

void test_mod_validate_empty_version() {
    auto desc = atlas::plugin::ModManifestParser::Parse("TestMod", "");
    auto result = atlas::plugin::ModManifestParser::Validate(desc);
    assert(result == atlas::plugin::ModLoadResult::EmptyVersion);
    std::cout << "[PASS] test_mod_validate_empty_version" << std::endl;
}

void test_mod_register() {
    atlas::plugin::ModRegistry registry;
    auto desc = atlas::plugin::ModManifestParser::Parse("TestMod", "1.0.0");
    auto result = registry.Register(desc);
    assert(result == atlas::plugin::ModLoadResult::Success);
    assert(registry.ModCount() == 1);
    assert(registry.Find("TestMod") != nullptr);
    assert(registry.Find("TestMod")->name == "TestMod");
    std::cout << "[PASS] test_mod_register" << std::endl;
}

void test_mod_sorted() {
    atlas::plugin::ModRegistry registry;
    registry.Register(atlas::plugin::ModManifestParser::Parse("ModC", "1.0.0", "", 30));
    registry.Register(atlas::plugin::ModManifestParser::Parse("ModA", "1.0.0", "", 10));
    registry.Register(atlas::plugin::ModManifestParser::Parse("ModB", "1.0.0", "", 20));

    auto sorted = registry.GetSorted();
    assert(sorted.size() == 3);
    assert(sorted[0].name == "ModA");
    assert(sorted[1].name == "ModB");
    assert(sorted[2].name == "ModC");
    std::cout << "[PASS] test_mod_sorted" << std::endl;
}

void test_mod_dependencies_met() {
    atlas::plugin::ModRegistry registry;

    atlas::plugin::ModDescriptor base;
    base.name = "BaseMod";
    base.version = "1.0.0";
    registry.Register(base);

    atlas::plugin::ModDescriptor dependent;
    dependent.name = "DepMod";
    dependent.version = "1.0.0";
    dependent.dependencies = {{"BaseMod", "1.0.0"}};
    registry.Register(dependent);

    assert(registry.AreDependenciesMet("DepMod"));
    std::cout << "[PASS] test_mod_dependencies_met" << std::endl;
}

void test_mod_dependencies_missing() {
    atlas::plugin::ModRegistry registry;

    atlas::plugin::ModDescriptor dependent;
    dependent.name = "DepMod";
    dependent.version = "1.0.0";
    dependent.dependencies = {{"MissingMod", "1.0.0"}};
    registry.Register(dependent);

    assert(!registry.AreDependenciesMet("DepMod"));
    std::cout << "[PASS] test_mod_dependencies_missing" << std::endl;
}

void test_mod_clear() {
    atlas::plugin::ModRegistry registry;
    registry.Register(atlas::plugin::ModManifestParser::Parse("TestMod", "1.0.0"));
    assert(registry.ModCount() == 1);
    registry.Clear();
    assert(registry.ModCount() == 0);
    assert(registry.Find("TestMod") == nullptr);
    std::cout << "[PASS] test_mod_clear" << std::endl;
}
