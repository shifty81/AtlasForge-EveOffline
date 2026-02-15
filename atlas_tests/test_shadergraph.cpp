#include "../engine/shader/ShaderGraph.h"
#include "../engine/shader/ShaderNodes.h"
#include <iostream>
#include <cassert>
#include <cmath>

void test_shadergraph_add_nodes() {
    atlas::shader::ShaderGraph graph;
    auto id = graph.AddNode(std::make_unique<atlas::shader::MultiplyNode>());
    assert(id == 1);
    assert(graph.NodeCount() == 1);
    std::cout << "[PASS] test_shadergraph_add_nodes" << std::endl;
}

void test_shadergraph_remove_node() {
    atlas::shader::ShaderGraph graph;
    auto id = graph.AddNode(std::make_unique<atlas::shader::MultiplyNode>());
    graph.RemoveNode(id);
    assert(graph.NodeCount() == 0);
    std::cout << "[PASS] test_shadergraph_remove_node" << std::endl;
}

void test_shadergraph_compile_empty() {
    atlas::shader::ShaderGraph graph;
    assert(graph.Compile());
    assert(graph.IsCompiled());
    std::cout << "[PASS] test_shadergraph_compile_empty" << std::endl;
}

void test_shadergraph_compile_single_node() {
    atlas::shader::ShaderGraph graph;
    auto id = graph.AddNode(std::make_unique<atlas::shader::UVCoordNode>());
    assert(graph.Compile());

    atlas::shader::ShaderContext ctx{0.5f, 0.75f, 42};
    assert(graph.Execute(ctx));

    auto* output = graph.GetOutput(id, 0);
    assert(output != nullptr);
    assert(output->type == atlas::shader::ShaderPinType::Vec2);
    assert(output->data.size() == 2);
    assert(std::fabs(output->data[0] - 0.5f) < 1e-5f);
    assert(std::fabs(output->data[1] - 0.75f) < 1e-5f);
    std::cout << "[PASS] test_shadergraph_compile_single_node" << std::endl;
}

void test_shadergraph_compile_chain() {
    atlas::shader::ShaderGraph graph;

    auto mul1 = graph.AddNode(std::make_unique<atlas::shader::MultiplyNode>());
    auto mul2 = graph.AddNode(std::make_unique<atlas::shader::MultiplyNode>());

    // Chain: MultiplyNode Float out -> MultiplyNode Float in
    graph.AddEdge({mul1, 0, mul2, 0});

    assert(graph.Compile());

    atlas::shader::ShaderContext ctx{0.5f, 0.75f, 42};
    assert(graph.Execute(ctx));

    auto* output = graph.GetOutput(mul2, 0);
    assert(output != nullptr);
    assert(output->type == atlas::shader::ShaderPinType::Float);
    // mul1: 1.0*1.0=1.0, mul2: 1.0*1.0=1.0
    assert(std::fabs(output->data[0] - 1.0f) < 1e-5f);
    std::cout << "[PASS] test_shadergraph_compile_chain" << std::endl;
}

void test_shadergraph_execute() {
    atlas::shader::ShaderGraph graph;

    auto baseId = graph.AddNode(std::make_unique<atlas::shader::BaseColorNode>());
    assert(graph.Compile());

    atlas::shader::ShaderContext ctx{0.5f, 0.75f, 42};
    assert(graph.Execute(ctx));

    // Albedo (port 0)
    auto* albedo = graph.GetOutput(baseId, 0);
    assert(albedo != nullptr);
    assert(albedo->type == atlas::shader::ShaderPinType::Vec3);
    assert(albedo->data.size() == 3);
    assert(std::fabs(albedo->data[0] - 0.8f) < 1e-5f);
    assert(std::fabs(albedo->data[1] - 0.8f) < 1e-5f);
    assert(std::fabs(albedo->data[2] - 0.8f) < 1e-5f);

    // Roughness (port 1)
    auto* roughness = graph.GetOutput(baseId, 1);
    assert(roughness != nullptr);
    assert(roughness->data.size() == 1);
    assert(std::fabs(roughness->data[0] - 0.5f) < 1e-5f);

    // Metallic (port 2)
    auto* metallic = graph.GetOutput(baseId, 2);
    assert(metallic != nullptr);
    assert(metallic->data.size() == 1);
    assert(std::fabs(metallic->data[0] - 0.0f) < 1e-5f);

    std::cout << "[PASS] test_shadergraph_execute" << std::endl;
}

void test_shadergraph_lerp_node() {
    atlas::shader::ShaderGraph graph;

    auto lerpId = graph.AddNode(std::make_unique<atlas::shader::LerpNode>());
    assert(graph.Compile());

    atlas::shader::ShaderContext ctx{0.5f, 0.75f, 42};
    assert(graph.Execute(ctx));

    // Default: A={0,0,0}, B={1,1,1}, T=0.5 -> Result={0.5, 0.5, 0.5}
    auto* result = graph.GetOutput(lerpId, 0);
    assert(result != nullptr);
    assert(result->type == atlas::shader::ShaderPinType::Vec3);
    assert(result->data.size() == 3);
    assert(std::fabs(result->data[0] - 0.5f) < 1e-5f);
    assert(std::fabs(result->data[1] - 0.5f) < 1e-5f);
    assert(std::fabs(result->data[2] - 0.5f) < 1e-5f);

    std::cout << "[PASS] test_shadergraph_lerp_node" << std::endl;
}

void test_shadergraph_deterministic() {
    auto buildAndRun = [](uint64_t seed) -> std::vector<float> {
        atlas::shader::ShaderGraph graph;
        auto mulId = graph.AddNode(std::make_unique<atlas::shader::MultiplyNode>());
        auto baseId = graph.AddNode(std::make_unique<atlas::shader::BaseColorNode>());
        graph.Compile();
        atlas::shader::ShaderContext ctx{0.5f, 0.75f, seed};
        graph.Execute(ctx);
        return graph.GetOutput(baseId, 0)->data;
    };

    auto a = buildAndRun(42);
    auto b = buildAndRun(42);
    assert(a == b);

    auto c = buildAndRun(42);
    assert(a == c);
    std::cout << "[PASS] test_shadergraph_deterministic" << std::endl;
}
