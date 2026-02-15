#include "../engine/render/RenderGraph.h"
#include "../engine/render/RenderNodes.h"
#include <iostream>
#include <cassert>
#include <cmath>

void test_rendergraph_add_nodes() {
    atlas::render::RenderGraph graph;
    auto id = graph.AddNode(std::make_unique<atlas::render::ClearPassNode>());
    assert(id == 1);
    assert(graph.NodeCount() == 1);
    std::cout << "[PASS] test_rendergraph_add_nodes" << std::endl;
}

void test_rendergraph_remove_node() {
    atlas::render::RenderGraph graph;
    auto id = graph.AddNode(std::make_unique<atlas::render::ClearPassNode>());
    graph.RemoveNode(id);
    assert(graph.NodeCount() == 0);
    std::cout << "[PASS] test_rendergraph_remove_node" << std::endl;
}

void test_rendergraph_compile_empty() {
    atlas::render::RenderGraph graph;
    assert(graph.Compile());
    assert(graph.IsCompiled());
    std::cout << "[PASS] test_rendergraph_compile_empty" << std::endl;
}

void test_rendergraph_compile_single_node() {
    atlas::render::RenderGraph graph;
    auto id = graph.AddNode(std::make_unique<atlas::render::ClearPassNode>());
    assert(graph.Compile());

    atlas::render::RenderContext ctx{4, 4, 0, 42};
    assert(graph.Execute(ctx));

    auto* output = graph.GetOutput(id, 0);
    assert(output != nullptr);
    assert(output->type == atlas::render::RenderPinType::Texture);
    assert(output->data.size() == 4 * 4 * 4);
    std::cout << "[PASS] test_rendergraph_compile_single_node" << std::endl;
}

void test_rendergraph_compile_chain() {
    atlas::render::RenderGraph graph;

    auto clearId = graph.AddNode(std::make_unique<atlas::render::ClearPassNode>());
    auto postId = graph.AddNode(std::make_unique<atlas::render::PostProcessNode>());

    // ClearPass Texture output -> PostProcess Texture input
    graph.AddEdge({clearId, 0, postId, 0});

    assert(graph.Compile());

    atlas::render::RenderContext ctx{4, 4, 0, 42};
    assert(graph.Execute(ctx));

    auto* output = graph.GetOutput(postId, 0);
    assert(output != nullptr);
    assert(output->type == atlas::render::RenderPinType::Texture);
    assert(output->data.size() == 4 * 4 * 4);
    std::cout << "[PASS] test_rendergraph_compile_chain" << std::endl;
}

void test_rendergraph_execute() {
    atlas::render::RenderGraph graph;

    // Full pipeline: ClearPass -> GeometryPass -> PostProcess -> Present
    auto clearId = graph.AddNode(std::make_unique<atlas::render::ClearPassNode>());
    auto geomId = graph.AddNode(std::make_unique<atlas::render::GeometryPassNode>());
    auto postId = graph.AddNode(std::make_unique<atlas::render::PostProcessNode>());
    auto presentId = graph.AddNode(std::make_unique<atlas::render::PresentNode>());

    // ClearPass ColorTarget -> GeometryPass ColorTarget
    graph.AddEdge({clearId, 0, geomId, 0});
    // GeometryPass ColorOutput -> PostProcess ColorInput
    graph.AddEdge({geomId, 0, postId, 0});
    // PostProcess FinalColor -> Present FinalColor
    graph.AddEdge({postId, 0, presentId, 0});

    assert(graph.Compile());

    atlas::render::RenderContext ctx{4, 4, 0, 42};
    assert(graph.Execute(ctx));

    auto* output = graph.GetOutput(presentId, 0);
    assert(output != nullptr);
    assert(output->type == atlas::render::RenderPinType::Texture);
    assert(output->data.size() == 4 * 4 * 4);
    std::cout << "[PASS] test_rendergraph_execute" << std::endl;
}

void test_rendergraph_deterministic() {
    auto buildAndRun = [](uint64_t seed) -> std::vector<float> {
        atlas::render::RenderGraph graph;
        auto clearId = graph.AddNode(std::make_unique<atlas::render::ClearPassNode>());
        auto postId = graph.AddNode(std::make_unique<atlas::render::PostProcessNode>());
        graph.AddEdge({clearId, 0, postId, 0});
        graph.Compile();
        atlas::render::RenderContext ctx{4, 4, 0, seed};
        graph.Execute(ctx);
        return graph.GetOutput(postId, 0)->data;
    };

    auto a = buildAndRun(42);
    auto b = buildAndRun(42);
    assert(a == b);

    auto c = buildAndRun(42);
    assert(a == c);
    std::cout << "[PASS] test_rendergraph_deterministic" << std::endl;
}
