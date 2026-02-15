#include <cassert>
#include <iostream>
#include <memory>
#include "../engine/strategygraph/StrategyGraph.h"
#include "../engine/strategygraph/StrategyNodes.h"

using namespace atlas::strategy;

void test_strategygraph_add_nodes() {
    StrategyGraph graph;
    auto node = std::make_unique<InfluenceRingNode>();
    StrategyNodeID id = graph.AddNode(std::move(node));
    assert(id > 0);
    assert(graph.NodeCount() == 1);
    std::cout << "[PASS] test_strategygraph_add_nodes" << std::endl;
}

void test_strategygraph_remove_node() {
    StrategyGraph graph;
    auto node = std::make_unique<InfluenceRingNode>();
    StrategyNodeID id = graph.AddNode(std::move(node));
    graph.RemoveNode(id);
    assert(graph.NodeCount() == 0);
    std::cout << "[PASS] test_strategygraph_remove_node" << std::endl;
}

void test_strategygraph_compile_empty() {
    StrategyGraph graph;
    assert(graph.Compile() == true);
    std::cout << "[PASS] test_strategygraph_compile_empty" << std::endl;
}

void test_strategygraph_compile_single_node() {
    StrategyGraph graph;
    auto node = std::make_unique<InfluenceRingNode>();
    node->radius = 3000.0f;
    node->strength = 2.0f;
    graph.AddNode(std::move(node));
    assert(graph.Compile() == true);
    assert(graph.IsCompiled());
    std::cout << "[PASS] test_strategygraph_compile_single_node" << std::endl;
}

void test_strategygraph_compile_chain() {
    StrategyGraph graph;

    auto influence = std::make_unique<InfluenceRingNode>();
    influence->strength = 1.5f;
    StrategyNodeID n1 = graph.AddNode(std::move(influence));

    auto threat = std::make_unique<ThreatFieldNode>();
    StrategyNodeID n2 = graph.AddNode(std::move(threat));

    graph.AddEdge({ n1, 0, n2, 0 });

    assert(graph.Compile() == true);
    std::cout << "[PASS] test_strategygraph_compile_chain" << std::endl;
}

void test_strategygraph_execute() {
    StrategyGraph graph;

    auto influence = std::make_unique<InfluenceRingNode>();
    influence->strength = 2.0f;
    StrategyNodeID n1 = graph.AddNode(std::move(influence));

    auto threat = std::make_unique<ThreatFieldNode>();
    threat->hostilityWeight = 0.5f;
    StrategyNodeID n2 = graph.AddNode(std::move(threat));

    graph.AddEdge({ n1, 0, n2, 0 });

    assert(graph.Compile());

    StrategyContext ctx;
    ctx.tick = 1;
    ctx.seed = 42;
    assert(graph.Execute(ctx));

    // ThreatField output: strength(2.0) * hostilityWeight(0.5) = 1.0
    const StrategyValue* out = graph.GetOutput(n2, 0);
    assert(out != nullptr);
    assert(!out->data.empty());
    assert(out->data[0] >= 0.99f && out->data[0] <= 1.01f);

    std::cout << "[PASS] test_strategygraph_execute" << std::endl;
}

void test_strategygraph_deterministic() {
    auto buildAndExecute = [](uint64_t seed) -> float {
        StrategyGraph graph;

        auto influence = std::make_unique<InfluenceRingNode>();
        influence->strength = 1.5f;
        StrategyNodeID n1 = graph.AddNode(std::move(influence));

        auto threat = std::make_unique<ThreatFieldNode>();
        StrategyNodeID n2 = graph.AddNode(std::move(threat));

        auto score = std::make_unique<ObjectiveScoreNode>();
        score->controlWeight = 1.0f;
        score->threatWeight = -0.5f;
        StrategyNodeID n3 = graph.AddNode(std::move(score));

        graph.AddEdge({ n1, 0, n2, 0 });
        graph.AddEdge({ n1, 0, n3, 0 });
        graph.AddEdge({ n2, 0, n3, 1 });

        graph.Compile();

        StrategyContext ctx;
        ctx.seed = seed;
        graph.Execute(ctx);

        const StrategyValue* out = graph.GetOutput(n3, 0);
        return out ? out->data[0] : -999.0f;
    };

    float a = buildAndExecute(42);
    float b = buildAndExecute(42);
    assert(a == b);

    std::cout << "[PASS] test_strategygraph_deterministic" << std::endl;
}

void test_strategygraph_objective_score() {
    StrategyGraph graph;

    auto c1 = std::make_unique<StrategyConstantNode>();
    c1->value = 10.0f;
    StrategyNodeID n1 = graph.AddNode(std::move(c1));

    auto c2 = std::make_unique<StrategyConstantNode>();
    c2->value = 4.0f;
    StrategyNodeID n2 = graph.AddNode(std::move(c2));

    auto obj = std::make_unique<ObjectiveScoreNode>();
    obj->controlWeight = 1.0f;
    obj->threatWeight = -0.5f;
    StrategyNodeID n3 = graph.AddNode(std::move(obj));

    graph.AddEdge({ n1, 0, n3, 0 });
    graph.AddEdge({ n2, 0, n3, 1 });

    assert(graph.Compile());

    StrategyContext ctx;
    assert(graph.Execute(ctx));

    // score = 1.0 * 10.0 + (-0.5) * 4.0 = 10.0 - 2.0 = 8.0
    const StrategyValue* out = graph.GetOutput(n3, 0);
    assert(out != nullptr);
    assert(out->data[0] >= 7.99f && out->data[0] <= 8.01f);

    std::cout << "[PASS] test_strategygraph_objective_score" << std::endl;
}
