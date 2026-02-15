#pragma once
#include "../ui/EditorPanel.h"
#include "../../engine/ecs/ECS.h"
#include <string>
#include <vector>
#include <typeindex>

namespace atlas::editor {

class ECSInspectorPanel : public EditorPanel {
public:
    explicit ECSInspectorPanel(ecs::World& world) : m_world(world) {}

    const char* Name() const override { return "ECS Inspector"; }
    void Draw() override;

    /// Refresh cached entity snapshots from the ECS world.
    void Refresh();

    /// Snapshot of a single entity for display.
    struct EntitySnapshot {
        ecs::EntityID id = 0;
        std::vector<std::string> componentTypeNames;
    };

    const std::vector<EntitySnapshot>& GetEntities() const { return m_cache; }
    size_t EntityCount() const { return m_cache.size(); }

    /// Select an entity for detailed inspection.
    void SelectEntity(ecs::EntityID id) { m_selectedEntity = id; }
    ecs::EntityID SelectedEntity() const { return m_selectedEntity; }

private:
    ecs::World& m_world;
    std::vector<EntitySnapshot> m_cache;
    ecs::EntityID m_selectedEntity = 0;
};

}
