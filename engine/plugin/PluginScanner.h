#pragma once
#include <string>
#include <vector>

namespace atlas::plugin {

struct SymbolEntry {
    std::string name;
    bool required = false;
};

enum class ScanResult { Valid, MissingRequired, ForbiddenSymbol, EmptyBinary };

class PluginScanner {
public:
    void AddRequiredSymbol(const std::string& symbol);
    void AddForbiddenSymbol(const std::string& symbol);

    ScanResult Scan(const std::vector<std::string>& exportedSymbols) const;

    const std::vector<std::string>& RequiredSymbols() const;
    const std::vector<std::string>& ForbiddenSymbols() const;
    std::vector<std::string> MissingSymbols(const std::vector<std::string>& exportedSymbols) const;
    std::vector<std::string> FoundForbidden(const std::vector<std::string>& exportedSymbols) const;

    void Clear();

private:
    std::vector<std::string> m_required;
    std::vector<std::string> m_forbidden;
};

} // namespace atlas::plugin
