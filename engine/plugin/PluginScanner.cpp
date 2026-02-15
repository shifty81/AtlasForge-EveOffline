#include "PluginScanner.h"
#include <algorithm>

namespace atlas::plugin {

void PluginScanner::AddRequiredSymbol(const std::string& symbol) {
    m_required.push_back(symbol);
}

void PluginScanner::AddForbiddenSymbol(const std::string& symbol) {
    m_forbidden.push_back(symbol);
}

ScanResult PluginScanner::Scan(const std::vector<std::string>& exportedSymbols) const {
    if (exportedSymbols.empty()) {
        return ScanResult::EmptyBinary;
    }
    for (const auto& req : m_required) {
        if (std::find(exportedSymbols.begin(), exportedSymbols.end(), req) == exportedSymbols.end()) {
            return ScanResult::MissingRequired;
        }
    }
    for (const auto& forbid : m_forbidden) {
        if (std::find(exportedSymbols.begin(), exportedSymbols.end(), forbid) != exportedSymbols.end()) {
            return ScanResult::ForbiddenSymbol;
        }
    }
    return ScanResult::Valid;
}

const std::vector<std::string>& PluginScanner::RequiredSymbols() const {
    return m_required;
}

const std::vector<std::string>& PluginScanner::ForbiddenSymbols() const {
    return m_forbidden;
}

std::vector<std::string> PluginScanner::MissingSymbols(const std::vector<std::string>& exportedSymbols) const {
    std::vector<std::string> missing;
    for (const auto& req : m_required) {
        if (std::find(exportedSymbols.begin(), exportedSymbols.end(), req) == exportedSymbols.end()) {
            missing.push_back(req);
        }
    }
    return missing;
}

std::vector<std::string> PluginScanner::FoundForbidden(const std::vector<std::string>& exportedSymbols) const {
    std::vector<std::string> found;
    for (const auto& forbid : m_forbidden) {
        if (std::find(exportedSymbols.begin(), exportedSymbols.end(), forbid) != exportedSymbols.end()) {
            found.push_back(forbid);
        }
    }
    return found;
}

void PluginScanner::Clear() {
    m_required.clear();
    m_forbidden.clear();
}

} // namespace atlas::plugin
