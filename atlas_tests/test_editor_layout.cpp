#include "../editor/ui/EditorLayout.h"
#include <iostream>
#include <cassert>

using namespace atlas::editor;

// A simple test panel that tracks draw calls
class TestPanel : public EditorPanel {
public:
    TestPanel(const char* name) : m_name(name) {}
    const char* Name() const override { return m_name; }
    void Draw() override { m_drawCount++; }
    int DrawCount() const { return m_drawCount; }
private:
    const char* m_name;
    int m_drawCount = 0;
};

void test_editor_layout_register_panel() {
    EditorLayout layout;
    TestPanel p1("Panel1");
    TestPanel p2("Panel2");
    layout.RegisterPanel(&p1);
    layout.RegisterPanel(&p2);
    assert(layout.Panels().size() == 2);
    assert(layout.Panels()[0] == &p1);
    assert(layout.Panels()[1] == &p2);
    std::cout << "[PASS] test_editor_layout_register_panel" << std::endl;
}

void test_editor_layout_draw_leaf() {
    EditorLayout layout;
    TestPanel p("Leaf");
    layout.Root().panel = &p;
    layout.Draw();
    assert(p.DrawCount() == 1);
    std::cout << "[PASS] test_editor_layout_draw_leaf" << std::endl;
}

void test_editor_layout_draw_split() {
    EditorLayout layout;
    TestPanel left("Left");
    TestPanel right("Right");

    layout.Root().split = DockSplit::Horizontal;
    layout.Root().a = std::make_unique<DockNode>();
    layout.Root().b = std::make_unique<DockNode>();
    layout.Root().a->panel = &left;
    layout.Root().b->panel = &right;

    layout.Draw();
    assert(left.DrawCount() == 1);
    assert(right.DrawCount() == 1);
    std::cout << "[PASS] test_editor_layout_draw_split" << std::endl;
}

void test_editor_layout_hidden_panel() {
    EditorLayout layout;
    TestPanel p("Hidden");
    p.SetVisible(false);
    layout.Root().panel = &p;
    layout.Draw();
    assert(p.DrawCount() == 0);
    std::cout << "[PASS] test_editor_layout_hidden_panel" << std::endl;
}

void test_editor_layout_nested_split() {
    EditorLayout layout;
    TestPanel p1("TopLeft");
    TestPanel p2("TopRight");
    TestPanel p3("Bottom");

    // Root: vertical split
    layout.Root().split = DockSplit::Vertical;
    layout.Root().a = std::make_unique<DockNode>();
    layout.Root().b = std::make_unique<DockNode>();

    // Top: horizontal split
    layout.Root().a->split = DockSplit::Horizontal;
    layout.Root().a->a = std::make_unique<DockNode>();
    layout.Root().a->b = std::make_unique<DockNode>();
    layout.Root().a->a->panel = &p1;
    layout.Root().a->b->panel = &p2;

    // Bottom: leaf
    layout.Root().b->panel = &p3;

    layout.Draw();
    assert(p1.DrawCount() == 1);
    assert(p2.DrawCount() == 1);
    assert(p3.DrawCount() == 1);
    std::cout << "[PASS] test_editor_layout_nested_split" << std::endl;
}
