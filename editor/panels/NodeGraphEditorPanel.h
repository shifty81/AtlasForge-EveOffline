#pragma once
#include "../ui/EditorPanel.h"
#include "../../engine/nodeeditor/NodeEditorModel.h"
#include "../../engine/command/CommandHistory.h"
#include <string>
#include <functional>

namespace atlas::editor {

/// NodeGraphEditorPanel — generic visual node graph editor panel.
/// Can display and edit any graph type by populating a NodeEditorModel.
/// Provides node palette, canvas with pan/zoom, node inspector, and link management.
class NodeGraphEditorPanel : public EditorPanel {
public:
    const char* Name() const override { return "Node Graph Editor"; }
    void Draw() override;

    /// Set the model to display/edit.
    void SetModel(nodeeditor::NodeEditorModel* model) { m_model = model; }
    nodeeditor::NodeEditorModel* GetModel() { return m_model; }

    /// Set the command history for undo/redo support.
    void SetCommandHistory(command::CommandHistory* history) { m_history = history; }

    /// Get the currently selected node, or 0 if none.
    nodeeditor::NodeEditorNodeID SelectedNode() const { return m_selectedNode; }

    /// Get the current graph type label (e.g. "WorldGraph", "ShaderGraph").
    const std::string& GraphTypeLabel() const { return m_graphTypeLabel; }
    void SetGraphTypeLabel(const std::string& label) { m_graphTypeLabel = label; }

    /// Canvas interaction
    void Pan(float dx, float dy);
    void Zoom(float factor);
    void SelectNodeAt(nodeeditor::Vec2 point);
    void BeginLinkDrag(nodeeditor::PinID fromPin);
    bool CompleteLinkDrag(nodeeditor::PinID toPin);
    void CancelLinkDrag();

    bool IsLinkDragging() const { return m_draggingLink; }

private:
    nodeeditor::NodeEditorModel* m_model = nullptr;
    command::CommandHistory* m_history = nullptr;
    nodeeditor::NodeEditorNodeID m_selectedNode = 0;
    std::string m_graphTypeLabel = "Graph";

    // Link drag state
    bool m_draggingLink = false;
    nodeeditor::PinID m_dragFromPin = 0;
};

} // namespace atlas::editor
