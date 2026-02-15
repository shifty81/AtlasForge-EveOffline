#include "ECSInspectorPanel.h"

#ifdef __GNUC__
#include <cxxabi.h>
#include <cstdlib>
static std::string demangle(const char* name) {
    int status = 0;
    char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, &status);
    std::string result = (status == 0 && demangled) ? demangled : name;
    std::free(demangled);
    return result;
}
#else
static std::string demangle(const char* name) { return name; }
#endif

namespace atlas::editor {

void ECSInspectorPanel::Draw() {
    Refresh();
    // Rendering is handled by the Atlas UI system when connected.
    // The cached data (m_cache, m_selectedEntity) is available for
    // the UI layer to read and present.
}

void ECSInspectorPanel::Refresh() {
    m_cache.clear();
    auto entities = m_world.GetEntities();
    m_cache.reserve(entities.size());
    for (auto id : entities) {
        EntitySnapshot snap;
        snap.id = id;
        auto types = m_world.GetComponentTypes(id);
        snap.componentTypeNames.reserve(types.size());
        for (auto& ti : types) {
            snap.componentTypeNames.push_back(demangle(ti.name()));
        }
        m_cache.push_back(std::move(snap));
    }
}

}
