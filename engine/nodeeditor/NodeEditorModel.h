#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace atlas::nodeeditor {

using NodeEditorNodeID = uint32_t;
using PinID = uint32_t;

enum class PinKind : uint8_t {
    Input,
    Output
};

struct Vec2 {
    float x = 0.0f;
    float y = 0.0f;
};

struct PinDesc {
    PinID id;
    std::string name;
    std::string typeName;   // e.g. "Float", "Texture", "AudioBuffer"
    PinKind kind;
};

struct NodeDesc {
    NodeEditorNodeID id;
    std::string name;
    std::string category;   // e.g. "Math", "Input", "Material"
    Vec2 position;
    Vec2 size;              // computed layout size
    std::vector<PinDesc> pins;
};

struct LinkDesc {
    PinID fromPin;
    PinID toPin;
};

/// Canvas viewport state
struct CanvasState {
    Vec2 offset{0.0f, 0.0f};   // pan offset
    float zoom = 1.0f;
};

/// NodeEditorModel — the data model behind any visual node graph editor.
/// Holds node positions, pin descriptors, links, selection, and canvas state.
/// This is game-agnostic: the editor panel populates it from a concrete graph type.
class NodeEditorModel {
public:
    // --- Node management ---
    void AddNode(const NodeDesc& desc);
    void RemoveNode(NodeEditorNodeID id);
    const NodeDesc* GetNode(NodeEditorNodeID id) const;
    void SetNodePosition(NodeEditorNodeID id, Vec2 pos);
    size_t NodeCount() const;
    std::vector<NodeEditorNodeID> GetNodeIDs() const;

    // --- Link management ---
    bool AddLink(PinID fromPin, PinID toPin);
    bool RemoveLink(PinID fromPin, PinID toPin);
    const std::vector<LinkDesc>& GetLinks() const;
    size_t LinkCount() const;

    // --- Selection ---
    void Select(NodeEditorNodeID id);
    void Deselect(NodeEditorNodeID id);
    void ClearSelection();
    bool IsSelected(NodeEditorNodeID id) const;
    std::vector<NodeEditorNodeID> GetSelection() const;
    size_t SelectionCount() const;

    // --- Canvas ---
    void SetCanvasOffset(Vec2 offset);
    void SetCanvasZoom(float zoom);
    const CanvasState& GetCanvasState() const;

    // --- Hit testing ---
    NodeEditorNodeID HitTestNode(Vec2 point) const;
    PinID HitTestPin(Vec2 point, float radius = 8.0f) const;

    // --- Layout helpers ---
    Vec2 GetPinPosition(PinID pinId) const;

    void Clear();

private:
    std::unordered_map<NodeEditorNodeID, NodeDesc> m_nodes;
    std::vector<LinkDesc> m_links;
    std::unordered_set<NodeEditorNodeID> m_selection;
    CanvasState m_canvas;

    // Pin→Node lookup for fast hit testing
    std::unordered_map<PinID, NodeEditorNodeID> m_pinToNode;
};

} // namespace atlas::nodeeditor
