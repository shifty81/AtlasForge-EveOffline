#include "../engine/plugin/PluginScanner.h"
#include <iostream>
#include <cassert>

void test_scanner_valid() {
    atlas::plugin::PluginScanner scanner;
    scanner.AddRequiredSymbol("atlas_init");
    scanner.AddRequiredSymbol("atlas_shutdown");

    std::vector<std::string> exports = {"atlas_init", "atlas_shutdown", "helper_func"};
    auto result = scanner.Scan(exports);
    assert(result == atlas::plugin::ScanResult::Valid);
    std::cout << "[PASS] test_scanner_valid" << std::endl;
}

void test_scanner_missing_required() {
    atlas::plugin::PluginScanner scanner;
    scanner.AddRequiredSymbol("atlas_init");
    scanner.AddRequiredSymbol("atlas_shutdown");

    std::vector<std::string> exports = {"atlas_init", "helper_func"};
    auto result = scanner.Scan(exports);
    assert(result == atlas::plugin::ScanResult::MissingRequired);
    std::cout << "[PASS] test_scanner_missing_required" << std::endl;
}

void test_scanner_forbidden_found() {
    atlas::plugin::PluginScanner scanner;
    scanner.AddRequiredSymbol("atlas_init");
    scanner.AddForbiddenSymbol("malloc_hook");

    std::vector<std::string> exports = {"atlas_init", "malloc_hook"};
    auto result = scanner.Scan(exports);
    assert(result == atlas::plugin::ScanResult::ForbiddenSymbol);
    std::cout << "[PASS] test_scanner_forbidden_found" << std::endl;
}

void test_scanner_empty_binary() {
    atlas::plugin::PluginScanner scanner;
    scanner.AddRequiredSymbol("atlas_init");

    std::vector<std::string> exports = {};
    auto result = scanner.Scan(exports);
    assert(result == atlas::plugin::ScanResult::EmptyBinary);
    std::cout << "[PASS] test_scanner_empty_binary" << std::endl;
}

void test_scanner_missing_symbols_query() {
    atlas::plugin::PluginScanner scanner;
    scanner.AddRequiredSymbol("atlas_init");
    scanner.AddRequiredSymbol("atlas_shutdown");
    scanner.AddRequiredSymbol("atlas_version");

    std::vector<std::string> exports = {"atlas_init"};
    auto missing = scanner.MissingSymbols(exports);
    assert(missing.size() == 2);
    std::cout << "[PASS] test_scanner_missing_symbols_query" << std::endl;
}

void test_scanner_found_forbidden_query() {
    atlas::plugin::PluginScanner scanner;
    scanner.AddForbiddenSymbol("malloc_hook");
    scanner.AddForbiddenSymbol("dlopen");

    std::vector<std::string> exports = {"atlas_init", "dlopen"};
    auto found = scanner.FoundForbidden(exports);
    assert(found.size() == 1);
    assert(found[0] == "dlopen");
    std::cout << "[PASS] test_scanner_found_forbidden_query" << std::endl;
}

void test_scanner_clear() {
    atlas::plugin::PluginScanner scanner;
    scanner.AddRequiredSymbol("atlas_init");
    scanner.AddForbiddenSymbol("malloc_hook");
    scanner.Clear();
    assert(scanner.RequiredSymbols().empty());
    assert(scanner.ForbiddenSymbols().empty());
    std::cout << "[PASS] test_scanner_clear" << std::endl;
}
