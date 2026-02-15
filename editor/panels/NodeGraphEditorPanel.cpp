#include "NodeGraphEditorPanel.h"

namespace atlas::editor {

void NodeGraphEditorPanel::Draw() {
    // Stub: In a real implementation, this renders via Atlas UI system
    // Layout:
    //   Left panel:   Node Palette (categorized node types)
    //   Center:       Infinite 2D canvas with pan/zoom
    //                 Nodes rendered as rectangles with pin circles
    //                 Links rendered as bezier curves color-coded by pin type
    //   Right panel:  Node Inspector (selected node properties)
    //   Bottom bar:   Graph type label, node count, link count
}

void NodeGraphEditorPanel::Pan(float dx, float dy) {
    if (!m_model) return;
    auto state = m_model->GetCanvasState();
    m_model->SetCanvasOffset({state.offset.x + dx, state.offset.y + dy});
}

void NodeGraphEditorPanel::Zoom(float factor) {
    if (!m_model) return;
    auto state = m_model->GetCanvasState();
    float newZoom = state.zoom * factor;
    if (newZoom >= 0.1f && newZoom <= 10.0f) {
        m_model->SetCanvasZoom(newZoom);
    }
}

void NodeGraphEditorPanel::SelectNodeAt(nodeeditor::Vec2 point) {
    if (!m_model) return;
    m_model->ClearSelection();
    auto hit = m_model->HitTestNode(point);
    if (hit != 0) {
        m_model->Select(hit);
        m_selectedNode = hit;
    } else {
        m_selectedNode = 0;
    }
}

void NodeGraphEditorPanel::BeginLinkDrag(nodeeditor::PinID fromPin) {
    m_draggingLink = true;
    m_dragFromPin = fromPin;
}

bool NodeGraphEditorPanel::CompleteLinkDrag(nodeeditor::PinID toPin) {
    if (!m_draggingLink || !m_model) {
        m_draggingLink = false;
        return false;
    }
    bool ok = m_model->AddLink(m_dragFromPin, toPin);
    m_draggingLink = false;
    m_dragFromPin = 0;
    return ok;
}

void NodeGraphEditorPanel::CancelLinkDrag() {
    m_draggingLink = false;
    m_dragFromPin = 0;
}

} // namespace atlas::editor
