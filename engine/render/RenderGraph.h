#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

namespace atlas::render {

enum class RenderPinType : uint8_t {
    Texture,        // Texture resource (color, depth, etc.)
    Buffer,         // GPU buffer resource
    Float,          // Scalar parameter
    PassConfig,     // Render pass configuration
    DrawList        // List of draw commands
};

struct RenderValue {
    RenderPinType type;
    std::vector<float> data;  // Generic float data storage
    std::string tag;          // Resource identifier tag
};

struct RenderPort {
    std::string name;
    RenderPinType type;
};

using RenderNodeID = uint32_t;
using RenderPortID = uint16_t;

struct RenderEdge {
    RenderNodeID fromNode;
    RenderPortID fromPort;
    RenderNodeID toNode;
    RenderPortID toPort;
};

struct RenderContext {
    uint32_t width;       // Framebuffer width
    uint32_t height;      // Framebuffer height
    uint32_t frameIndex;  // Current frame number
    uint64_t seed;        // Deterministic seed
};

class RenderNode {
public:
    virtual ~RenderNode() = default;
    virtual const char* GetName() const = 0;
    virtual const char* GetCategory() const = 0;
    virtual std::vector<RenderPort> Inputs() const = 0;
    virtual std::vector<RenderPort> Outputs() const = 0;
    virtual void Evaluate(const RenderContext& ctx, const std::vector<RenderValue>& inputs, std::vector<RenderValue>& outputs) const = 0;
};

class RenderGraph {
public:
    RenderNodeID AddNode(std::unique_ptr<RenderNode> node);
    void RemoveNode(RenderNodeID id);
    void AddEdge(const RenderEdge& edge);
    void RemoveEdge(const RenderEdge& edge);
    bool Compile();
    bool Execute(const RenderContext& ctx);
    const RenderValue* GetOutput(RenderNodeID node, RenderPortID port) const;
    size_t NodeCount() const;
    bool IsCompiled() const;
private:
    RenderNodeID m_nextID = 1;
    std::unordered_map<RenderNodeID, std::unique_ptr<RenderNode>> m_nodes;
    std::vector<RenderEdge> m_edges;
    std::vector<RenderNodeID> m_executionOrder;
    bool m_compiled = false;
    std::unordered_map<uint64_t, RenderValue> m_outputs;
    bool HasCycle() const;
    bool ValidateEdgeTypes() const;
};

}
