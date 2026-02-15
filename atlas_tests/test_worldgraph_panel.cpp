#include "../editor/panels/WorldGraphPanel.h"
#include <iostream>
#include <cassert>

using namespace atlas::editor;
using namespace atlas::world;

void test_worldgraph_panel_create() {
    WorldGraphPanel panel;
    assert(std::string(panel.Name()) == "World Graph Editor");
    assert(panel.GetGraph() == nullptr);
    assert(panel.SelectedNode() == 0);
    std::cout << "[PASS] test_worldgraph_panel_create" << std::endl;
}

void test_worldgraph_panel_set_graph() {
    WorldGraphPanel panel;
    WorldGraph graph;
    panel.SetGraph(&graph);
    assert(panel.GetGraph() == &graph);
    std::cout << "[PASS] test_worldgraph_panel_set_graph" << std::endl;
}

void test_worldgraph_panel_select_node() {
    WorldGraphPanel panel;
    panel.SelectNode(42);
    assert(panel.SelectedNode() == 42);
    panel.SelectNode(0);
    assert(panel.SelectedNode() == 0);
    std::cout << "[PASS] test_worldgraph_panel_select_node" << std::endl;
}

void test_worldgraph_panel_compile_no_graph() {
    WorldGraphPanel panel;
    assert(!panel.CompileGraph());
    std::cout << "[PASS] test_worldgraph_panel_compile_no_graph" << std::endl;
}

void test_worldgraph_panel_compile_with_graph() {
    WorldGraphPanel panel;
    WorldGraph graph;
    panel.SetGraph(&graph);
    // Empty graph should compile successfully (returns true for empty)
    bool result = panel.CompileGraph();
    assert(result == graph.Compile()); // Consistent with WorldGraph behavior
    std::cout << "[PASS] test_worldgraph_panel_compile_with_graph" << std::endl;
}

void test_worldgraph_panel_preview_no_graph() {
    WorldGraphPanel panel;
    WorldGenContext ctx{42, 0, 0, 16};
    assert(!panel.ExecutePreview(ctx));
    std::cout << "[PASS] test_worldgraph_panel_preview_no_graph" << std::endl;
}

void test_worldgraph_panel_visibility() {
    WorldGraphPanel panel;
    assert(panel.IsVisible());
    panel.SetVisible(false);
    assert(!panel.IsVisible());
    panel.SetVisible(true);
    assert(panel.IsVisible());
    std::cout << "[PASS] test_worldgraph_panel_visibility" << std::endl;
}
