#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

namespace atlas::shader {

enum class ShaderPinType : uint8_t {
    Float,          // Scalar value
    Vec2,           // 2D vector
    Vec3,           // 3D vector (color, normal, position)
    Vec4,           // 4D vector (color with alpha)
    Texture,        // Texture sample reference
    Bool            // Boolean for branching
};

struct ShaderValue {
    ShaderPinType type;
    std::vector<float> data;
};

struct ShaderPort {
    std::string name;
    ShaderPinType type;
};

using ShaderNodeID = uint32_t;
using ShaderPortID = uint16_t;

struct ShaderEdge {
    ShaderNodeID fromNode;
    ShaderPortID fromPort;
    ShaderNodeID toNode;
    ShaderPortID toPort;
};

struct ShaderContext {
    float u, v;           // UV coordinates for evaluation
    uint64_t seed;        // Deterministic seed
};

class ShaderNode {
public:
    virtual ~ShaderNode() = default;
    virtual const char* GetName() const = 0;
    virtual const char* GetCategory() const = 0;
    virtual std::vector<ShaderPort> Inputs() const = 0;
    virtual std::vector<ShaderPort> Outputs() const = 0;
    virtual void Evaluate(const ShaderContext& ctx, const std::vector<ShaderValue>& inputs, std::vector<ShaderValue>& outputs) const = 0;
};

class ShaderGraph {
public:
    ShaderNodeID AddNode(std::unique_ptr<ShaderNode> node);
    void RemoveNode(ShaderNodeID id);
    void AddEdge(const ShaderEdge& edge);
    void RemoveEdge(const ShaderEdge& edge);
    bool Compile();
    bool Execute(const ShaderContext& ctx);
    const ShaderValue* GetOutput(ShaderNodeID node, ShaderPortID port) const;
    size_t NodeCount() const;
    bool IsCompiled() const;
private:
    ShaderNodeID m_nextID = 1;
    std::unordered_map<ShaderNodeID, std::unique_ptr<ShaderNode>> m_nodes;
    std::vector<ShaderEdge> m_edges;
    std::vector<ShaderNodeID> m_executionOrder;
    bool m_compiled = false;
    std::unordered_map<uint64_t, ShaderValue> m_outputs;
    bool HasCycle() const;
    bool ValidateEdgeTypes() const;
};

}
