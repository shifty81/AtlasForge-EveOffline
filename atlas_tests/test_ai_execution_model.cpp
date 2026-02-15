#include <cassert>
#include <iostream>
#include "../engine/ai/AIExecutionModel.h"

using namespace atlas::ai;

void test_ai_exec_init() {
    AIExecutionModel model;
    AIExecutionConfig cfg;
    cfg.mode = AIExecutionMode::Standalone;
    model.Init(cfg);
    assert(model.Mode() == AIExecutionMode::Standalone);
    std::cout << "[PASS] test_ai_exec_init" << std::endl;
}

void test_ai_exec_authority() {
    AIExecutionModel model;
    AIExecutionConfig cfg;

    cfg.mode = AIExecutionMode::Standalone;
    model.Init(cfg);
    assert(model.IsAuthority());
    assert(model.CanExecuteGraphs());

    cfg.mode = AIExecutionMode::ServerAuthoritative;
    model.Init(cfg);
    assert(model.IsAuthority());
    assert(model.CanExecuteGraphs());

    cfg.mode = AIExecutionMode::ClientVisualization;
    model.Init(cfg);
    assert(!model.IsAuthority());
    assert(!model.CanExecuteGraphs());

    std::cout << "[PASS] test_ai_exec_authority" << std::endl;
}

void test_ai_exec_submit() {
    AIExecutionModel model;
    AIExecutionConfig cfg;
    cfg.mode = AIExecutionMode::Standalone;
    model.Init(cfg);

    bool ok = model.Submit("graph_001", 10);
    assert(ok);
    assert(model.PendingCount() == 1);
    assert(model.ResultCount() == 1);
    std::cout << "[PASS] test_ai_exec_submit" << std::endl;
}

void test_ai_exec_submit_rejected() {
    AIExecutionModel model;
    AIExecutionConfig cfg;
    cfg.mode = AIExecutionMode::ClientVisualization;
    model.Init(cfg);

    bool ok = model.Submit("graph_001", 10);
    assert(!ok);
    assert(model.PendingCount() == 0);
    assert(model.ResultCount() == 0);
    std::cout << "[PASS] test_ai_exec_submit_rejected" << std::endl;
}

void test_ai_exec_results() {
    AIExecutionModel model;
    AIExecutionConfig cfg;
    cfg.mode = AIExecutionMode::ServerAuthoritative;
    model.Init(cfg);

    model.Submit("graph_a", 5);
    model.Submit("graph_b", 5);
    model.Submit("graph_c", 10);

    auto tick5 = model.GetResults(5);
    assert(tick5.size() == 2);

    auto tick10 = model.GetResults(10);
    assert(tick10.size() == 1);
    assert(tick10[0].graphID == "graph_c");

    std::cout << "[PASS] test_ai_exec_results" << std::endl;
}

void test_ai_exec_receive_result() {
    AIExecutionModel model;
    AIExecutionConfig cfg;
    cfg.mode = AIExecutionMode::ClientVisualization;
    model.Init(cfg);

    AIExecutionResult result;
    result.graphID = "server_graph";
    result.tick = 42;
    result.executed = true;
    result.action = "attack";
    result.confidence = 0.9f;
    model.ReceiveResult(result);

    assert(model.ResultCount() == 1);
    auto results = model.GetResults(42);
    assert(results.size() == 1);
    assert(results[0].action == "attack");

    std::cout << "[PASS] test_ai_exec_receive_result" << std::endl;
}

void test_ai_exec_shutdown() {
    AIExecutionModel model;
    AIExecutionConfig cfg;
    cfg.mode = AIExecutionMode::ServerAuthoritative;
    model.Init(cfg);
    model.Submit("graph_x", 1);

    model.Shutdown();
    assert(model.Mode() == AIExecutionMode::Standalone);
    assert(model.PendingCount() == 0);
    assert(model.ResultCount() == 0);
    std::cout << "[PASS] test_ai_exec_shutdown" << std::endl;
}

void test_ai_exec_clear() {
    AIExecutionModel model;
    AIExecutionConfig cfg;
    cfg.mode = AIExecutionMode::Standalone;
    model.Init(cfg);
    model.Submit("g1", 1);
    model.Submit("g2", 2);
    assert(model.PendingCount() == 2);
    assert(model.ResultCount() == 2);

    model.Clear();
    assert(model.PendingCount() == 0);
    assert(model.ResultCount() == 0);
    std::cout << "[PASS] test_ai_exec_clear" << std::endl;
}
