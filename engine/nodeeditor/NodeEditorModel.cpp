#include "NodeEditorModel.h"
#include <algorithm>

namespace atlas::nodeeditor {

static constexpr float kPinHeaderOffset = 24.0f;
static constexpr float kPinSpacing      = 20.0f;

void NodeEditorModel::AddNode(const NodeDesc& desc) {
    m_nodes[desc.id] = desc;
    for (const auto& pin : desc.pins) {
        m_pinToNode[pin.id] = desc.id;
    }
}

void NodeEditorModel::RemoveNode(NodeEditorNodeID id) {
    auto it = m_nodes.find(id);
    if (it == m_nodes.end()) return;

    // Remove all links connected to this node's pins
    for (const auto& pin : it->second.pins) {
        m_pinToNode.erase(pin.id);
    }

    // Remove links referencing any pin of this node
    std::unordered_set<PinID> nodePins;
    for (const auto& pin : it->second.pins) {
        nodePins.insert(pin.id);
    }
    m_links.erase(
        std::remove_if(m_links.begin(), m_links.end(),
            [&](const LinkDesc& link) {
                return nodePins.count(link.fromPin) || nodePins.count(link.toPin);
            }),
        m_links.end());

    m_selection.erase(id);
    m_nodes.erase(it);
}

const NodeDesc* NodeEditorModel::GetNode(NodeEditorNodeID id) const {
    auto it = m_nodes.find(id);
    return it != m_nodes.end() ? &it->second : nullptr;
}

void NodeEditorModel::SetNodePosition(NodeEditorNodeID id, Vec2 pos) {
    auto it = m_nodes.find(id);
    if (it != m_nodes.end()) {
        it->second.position = pos;
    }
}

size_t NodeEditorModel::NodeCount() const {
    return m_nodes.size();
}

std::vector<NodeEditorNodeID> NodeEditorModel::GetNodeIDs() const {
    std::vector<NodeEditorNodeID> ids;
    ids.reserve(m_nodes.size());
    for (const auto& [id, _] : m_nodes) {
        ids.push_back(id);
    }
    return ids;
}

bool NodeEditorModel::AddLink(PinID fromPin, PinID toPin) {
    // Check both pins exist
    if (m_pinToNode.find(fromPin) == m_pinToNode.end() ||
        m_pinToNode.find(toPin) == m_pinToNode.end()) {
        return false;
    }
    // Prevent duplicate links
    for (const auto& link : m_links) {
        if (link.fromPin == fromPin && link.toPin == toPin) return false;
    }
    m_links.push_back({fromPin, toPin});
    return true;
}

bool NodeEditorModel::RemoveLink(PinID fromPin, PinID toPin) {
    auto it = std::find_if(m_links.begin(), m_links.end(),
        [&](const LinkDesc& link) {
            return link.fromPin == fromPin && link.toPin == toPin;
        });
    if (it == m_links.end()) return false;
    m_links.erase(it);
    return true;
}

const std::vector<LinkDesc>& NodeEditorModel::GetLinks() const {
    return m_links;
}

size_t NodeEditorModel::LinkCount() const {
    return m_links.size();
}

void NodeEditorModel::Select(NodeEditorNodeID id) {
    if (m_nodes.count(id)) {
        m_selection.insert(id);
    }
}

void NodeEditorModel::Deselect(NodeEditorNodeID id) {
    m_selection.erase(id);
}

void NodeEditorModel::ClearSelection() {
    m_selection.clear();
}

bool NodeEditorModel::IsSelected(NodeEditorNodeID id) const {
    return m_selection.count(id) > 0;
}

std::vector<NodeEditorNodeID> NodeEditorModel::GetSelection() const {
    return {m_selection.begin(), m_selection.end()};
}

size_t NodeEditorModel::SelectionCount() const {
    return m_selection.size();
}

void NodeEditorModel::SetCanvasOffset(Vec2 offset) {
    m_canvas.offset = offset;
}

void NodeEditorModel::SetCanvasZoom(float zoom) {
    if (zoom > 0.0f) {
        m_canvas.zoom = zoom;
    }
}

const CanvasState& NodeEditorModel::GetCanvasState() const {
    return m_canvas;
}

NodeEditorNodeID NodeEditorModel::HitTestNode(Vec2 point) const {
    for (const auto& [id, node] : m_nodes) {
        if (point.x >= node.position.x && point.x <= node.position.x + node.size.x &&
            point.y >= node.position.y && point.y <= node.position.y + node.size.y) {
            return id;
        }
    }
    return 0; // 0 means no hit
}

PinID NodeEditorModel::HitTestPin(Vec2 point, float radius) const {
    for (const auto& [id, node] : m_nodes) {
        float pinY = node.position.y + kPinHeaderOffset;
        for (const auto& pin : node.pins) {
            float pinX = (pin.kind == PinKind::Input)
                ? node.position.x
                : node.position.x + node.size.x;
            float dx = point.x - pinX;
            float dy = point.y - pinY;
            if (dx * dx + dy * dy <= radius * radius) {
                return pin.id;
            }
            pinY += kPinSpacing;
        }
    }
    return 0; // 0 means no hit
}

Vec2 NodeEditorModel::GetPinPosition(PinID pinId) const {
    auto nodeIt = m_pinToNode.find(pinId);
    if (nodeIt == m_pinToNode.end()) return {0.0f, 0.0f};

    auto it = m_nodes.find(nodeIt->second);
    if (it == m_nodes.end()) return {0.0f, 0.0f};

    const auto& node = it->second;
    float pinY = node.position.y + kPinHeaderOffset;
    for (const auto& pin : node.pins) {
        if (pin.id == pinId) {
            float pinX = (pin.kind == PinKind::Input)
                ? node.position.x
                : node.position.x + node.size.x;
            return {pinX, pinY};
        }
        pinY += kPinSpacing;
    }
    return {0.0f, 0.0f};
}

void NodeEditorModel::Clear() {
    m_nodes.clear();
    m_links.clear();
    m_selection.clear();
    m_pinToNode.clear();
    m_canvas = {};
}

} // namespace atlas::nodeeditor
