#include "../engine/nodeeditor/NodeEditorModel.h"
#include <iostream>
#include <cassert>

using namespace atlas::nodeeditor;

static NodeDesc MakeNode(NodeEditorNodeID id, const std::string& name,
                         float x, float y, float w, float h,
                         const std::vector<PinDesc>& pins) {
    return {id, name, "Test", {x, y}, {w, h}, pins};
}

void test_node_editor_add_node() {
    NodeEditorModel model;
    auto node = MakeNode(1, "Noise", 10, 20, 120, 80, {
        {100, "Seed", "Float", PinKind::Input},
        {101, "Output", "HeightField", PinKind::Output}
    });
    model.AddNode(node);
    assert(model.NodeCount() == 1);
    assert(model.GetNode(1) != nullptr);
    assert(model.GetNode(1)->name == "Noise");
    std::cout << "[PASS] test_node_editor_add_node" << std::endl;
}

void test_node_editor_remove_node() {
    NodeEditorModel model;
    model.AddNode(MakeNode(1, "A", 0, 0, 100, 60, {
        {100, "Out", "Float", PinKind::Output}
    }));
    model.AddNode(MakeNode(2, "B", 200, 0, 100, 60, {
        {200, "In", "Float", PinKind::Input}
    }));
    model.AddLink(100, 200);
    assert(model.LinkCount() == 1);

    model.RemoveNode(1);
    assert(model.NodeCount() == 1);
    assert(model.GetNode(1) == nullptr);
    // Links referencing removed node's pins should be cleaned up
    assert(model.LinkCount() == 0);
    std::cout << "[PASS] test_node_editor_remove_node" << std::endl;
}

void test_node_editor_set_position() {
    NodeEditorModel model;
    model.AddNode(MakeNode(1, "A", 0, 0, 100, 60, {}));
    model.SetNodePosition(1, {50.0f, 75.0f});
    auto* node = model.GetNode(1);
    assert(node != nullptr);
    assert(node->position.x == 50.0f);
    assert(node->position.y == 75.0f);
    std::cout << "[PASS] test_node_editor_set_position" << std::endl;
}

void test_node_editor_add_link() {
    NodeEditorModel model;
    model.AddNode(MakeNode(1, "A", 0, 0, 100, 60, {
        {100, "Out", "Float", PinKind::Output}
    }));
    model.AddNode(MakeNode(2, "B", 200, 0, 100, 60, {
        {200, "In", "Float", PinKind::Input}
    }));
    assert(model.AddLink(100, 200));
    assert(model.LinkCount() == 1);
    // Duplicate link should fail
    assert(!model.AddLink(100, 200));
    assert(model.LinkCount() == 1);
    std::cout << "[PASS] test_node_editor_add_link" << std::endl;
}

void test_node_editor_remove_link() {
    NodeEditorModel model;
    model.AddNode(MakeNode(1, "A", 0, 0, 100, 60, {
        {100, "Out", "Float", PinKind::Output}
    }));
    model.AddNode(MakeNode(2, "B", 200, 0, 100, 60, {
        {200, "In", "Float", PinKind::Input}
    }));
    model.AddLink(100, 200);
    assert(model.RemoveLink(100, 200));
    assert(model.LinkCount() == 0);
    // Removing again should fail
    assert(!model.RemoveLink(100, 200));
    std::cout << "[PASS] test_node_editor_remove_link" << std::endl;
}

void test_node_editor_link_invalid_pins() {
    NodeEditorModel model;
    model.AddNode(MakeNode(1, "A", 0, 0, 100, 60, {
        {100, "Out", "Float", PinKind::Output}
    }));
    // Link to non-existent pin should fail
    assert(!model.AddLink(100, 999));
    assert(model.LinkCount() == 0);
    std::cout << "[PASS] test_node_editor_link_invalid_pins" << std::endl;
}

void test_node_editor_selection() {
    NodeEditorModel model;
    model.AddNode(MakeNode(1, "A", 0, 0, 100, 60, {}));
    model.AddNode(MakeNode(2, "B", 200, 0, 100, 60, {}));
    model.AddNode(MakeNode(3, "C", 400, 0, 100, 60, {}));

    model.Select(1);
    model.Select(2);
    assert(model.SelectionCount() == 2);
    assert(model.IsSelected(1));
    assert(model.IsSelected(2));
    assert(!model.IsSelected(3));

    model.Deselect(1);
    assert(model.SelectionCount() == 1);
    assert(!model.IsSelected(1));

    model.ClearSelection();
    assert(model.SelectionCount() == 0);
    std::cout << "[PASS] test_node_editor_selection" << std::endl;
}

void test_node_editor_canvas() {
    NodeEditorModel model;
    model.SetCanvasOffset({100.0f, 200.0f});
    model.SetCanvasZoom(2.0f);

    auto state = model.GetCanvasState();
    assert(state.offset.x == 100.0f);
    assert(state.offset.y == 200.0f);
    assert(state.zoom == 2.0f);

    // Negative zoom should be ignored
    model.SetCanvasZoom(-1.0f);
    assert(model.GetCanvasState().zoom == 2.0f);
    std::cout << "[PASS] test_node_editor_canvas" << std::endl;
}

void test_node_editor_hit_test() {
    NodeEditorModel model;
    model.AddNode(MakeNode(1, "A", 10, 10, 100, 60, {}));
    model.AddNode(MakeNode(2, "B", 200, 200, 100, 60, {}));

    assert(model.HitTestNode({50, 40}) == 1);
    assert(model.HitTestNode({250, 230}) == 2);
    assert(model.HitTestNode({500, 500}) == 0); // miss
    std::cout << "[PASS] test_node_editor_hit_test" << std::endl;
}

void test_node_editor_clear() {
    NodeEditorModel model;
    model.AddNode(MakeNode(1, "A", 0, 0, 100, 60, {
        {100, "Out", "Float", PinKind::Output}
    }));
    model.AddNode(MakeNode(2, "B", 200, 0, 100, 60, {
        {200, "In", "Float", PinKind::Input}
    }));
    model.AddLink(100, 200);
    model.Select(1);

    model.Clear();
    assert(model.NodeCount() == 0);
    assert(model.LinkCount() == 0);
    assert(model.SelectionCount() == 0);
    std::cout << "[PASS] test_node_editor_clear" << std::endl;
}

void test_node_editor_get_node_ids() {
    NodeEditorModel model;
    model.AddNode(MakeNode(1, "A", 0, 0, 100, 60, {}));
    model.AddNode(MakeNode(5, "B", 0, 0, 100, 60, {}));
    model.AddNode(MakeNode(10, "C", 0, 0, 100, 60, {}));

    auto ids = model.GetNodeIDs();
    assert(ids.size() == 3);
    std::cout << "[PASS] test_node_editor_get_node_ids" << std::endl;
}

void test_node_editor_pin_position() {
    NodeEditorModel model;
    model.AddNode(MakeNode(1, "A", 100, 50, 120, 80, {
        {10, "In", "Float", PinKind::Input},
        {11, "Out", "Float", PinKind::Output}
    }));

    auto inPos = model.GetPinPosition(10);
    // Input pin: x == node.position.x (left edge)
    assert(inPos.x == 100.0f);

    auto outPos = model.GetPinPosition(11);
    // Output pin: x == node.position.x + node.size.x (right edge)
    assert(outPos.x == 220.0f);

    // Non-existent pin
    auto noPos = model.GetPinPosition(999);
    assert(noPos.x == 0.0f && noPos.y == 0.0f);
    std::cout << "[PASS] test_node_editor_pin_position" << std::endl;
}
