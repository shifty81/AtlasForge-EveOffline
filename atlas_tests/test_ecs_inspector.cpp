#include "../editor/panels/ECSInspectorPanel.h"
#include "../engine/ecs/ECS.h"
#include <iostream>
#include <cassert>

using namespace atlas::ecs;
using namespace atlas::editor;

struct TestComp {
    int value = 42;
};

void test_ecs_inspector_empty_world() {
    World world;
    ECSInspectorPanel panel(world);
    panel.Refresh();
    assert(panel.EntityCount() == 0);
    std::cout << "[PASS] test_ecs_inspector_empty_world" << std::endl;
}

void test_ecs_inspector_entity_list() {
    World world;
    EntityID e1 = world.CreateEntity();
    world.CreateEntity();
    ECSInspectorPanel panel(world);
    panel.Refresh();
    assert(panel.EntityCount() == 2);
    assert(panel.GetEntities()[0].id == e1);
    std::cout << "[PASS] test_ecs_inspector_entity_list" << std::endl;
}

void test_ecs_inspector_component_types() {
    World world;
    EntityID e = world.CreateEntity();
    world.AddComponent(e, TestComp{99});
    ECSInspectorPanel panel(world);
    panel.Refresh();
    assert(panel.EntityCount() == 1);
    assert(panel.GetEntities()[0].componentTypeNames.size() == 1);
    std::cout << "[PASS] test_ecs_inspector_component_types" << std::endl;
}

void test_ecs_inspector_select_entity() {
    World world;
    EntityID e = world.CreateEntity();
    ECSInspectorPanel panel(world);
    panel.SelectEntity(e);
    assert(panel.SelectedEntity() == e);
    std::cout << "[PASS] test_ecs_inspector_select_entity" << std::endl;
}

void test_ecs_inspector_draw_calls_refresh() {
    World world;
    world.CreateEntity();
    ECSInspectorPanel panel(world);
    assert(panel.EntityCount() == 0);
    panel.Draw();
    assert(panel.EntityCount() == 1);
    std::cout << "[PASS] test_ecs_inspector_draw_calls_refresh" << std::endl;
}
