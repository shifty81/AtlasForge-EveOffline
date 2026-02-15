#include <cassert>
#include <iostream>
#include "../engine/ai/AIVisualization.h"

using namespace atlas::ai;

void test_ai_viz_update_entity() {
    AIVisualization viz;
    viz.UpdateEntity(1, "patrol", 0.9f, 10, "graph_a");

    const AIVisualState* state = viz.GetEntityState(1);
    assert(state != nullptr);
    assert(state->entityID == 1);
    assert(state->currentAction == "patrol");
    assert(state->confidence > 0.89f && state->confidence < 0.91f);
    assert(state->lastUpdateTick == 10);
    assert(state->graphID == "graph_a");
    std::cout << "[PASS] test_ai_viz_update_entity" << std::endl;
}

void test_ai_viz_has_entity() {
    AIVisualization viz;
    assert(!viz.HasEntity(42));
    viz.UpdateEntity(42, "idle", 1.0f, 0);
    assert(viz.HasEntity(42));
    std::cout << "[PASS] test_ai_viz_has_entity" << std::endl;
}

void test_ai_viz_get_active() {
    AIVisualization viz;
    viz.UpdateEntity(1, "patrol", 0.8f, 5);
    viz.UpdateEntity(2, "attack", 0.9f, 5);
    viz.UpdateEntity(3, "flee", 0.7f, 5);

    auto active = viz.GetActiveEntities();
    assert(active.size() == 3);
    std::cout << "[PASS] test_ai_viz_get_active" << std::endl;
}

void test_ai_viz_stale_detection() {
    AIVisualization viz;
    viz.UpdateEntity(1, "patrol", 0.8f, 5);
    viz.UpdateEntity(2, "attack", 0.9f, 10);
    viz.UpdateEntity(3, "idle", 0.5f, 15);

    // At tick 20 with threshold 8: entity 1 (20-5=15 > 8) and entity 2 (20-10=10 > 8) are stale
    auto stale = viz.GetStaleEntities(20, 8);
    assert(stale.size() == 2);
    std::cout << "[PASS] test_ai_viz_stale_detection" << std::endl;
}

void test_ai_viz_purge_stale() {
    AIVisualization viz;
    viz.UpdateEntity(1, "patrol", 0.8f, 5);
    viz.UpdateEntity(2, "attack", 0.9f, 10);
    viz.UpdateEntity(3, "idle", 0.5f, 15);

    viz.PurgeStale(20, 8);
    assert(viz.EntityCount() == 1);
    assert(viz.HasEntity(3));
    assert(!viz.HasEntity(1));
    assert(!viz.HasEntity(2));
    std::cout << "[PASS] test_ai_viz_purge_stale" << std::endl;
}

void test_ai_viz_entity_count() {
    AIVisualization viz;
    assert(viz.EntityCount() == 0);
    viz.UpdateEntity(1, "idle", 1.0f, 0);
    viz.UpdateEntity(2, "idle", 1.0f, 0);
    assert(viz.EntityCount() == 2);
    std::cout << "[PASS] test_ai_viz_entity_count" << std::endl;
}

void test_ai_viz_clear() {
    AIVisualization viz;
    viz.UpdateEntity(1, "idle", 1.0f, 0);
    viz.UpdateEntity(2, "idle", 1.0f, 0);
    assert(viz.EntityCount() == 2);
    viz.Clear();
    assert(viz.EntityCount() == 0);
    std::cout << "[PASS] test_ai_viz_clear" << std::endl;
}

void test_ai_viz_missing_entity() {
    AIVisualization viz;
    const AIVisualState* state = viz.GetEntityState(999);
    assert(state == nullptr);
    std::cout << "[PASS] test_ai_viz_missing_entity" << std::endl;
}
