#pragma once
#include "ShaderGraph.h"

namespace atlas::shader {

// Math: Multiplies two float inputs
class MultiplyNode : public ShaderNode {
public:
    const char* GetName() const override { return "Multiply"; }
    const char* GetCategory() const override { return "Math"; }
    std::vector<ShaderPort> Inputs() const override;
    std::vector<ShaderPort> Outputs() const override;
    void Evaluate(const ShaderContext& ctx, const std::vector<ShaderValue>& inputs, std::vector<ShaderValue>& outputs) const override;
};

// Math: Linear interpolation between two Vec3 values
class LerpNode : public ShaderNode {
public:
    const char* GetName() const override { return "Lerp"; }
    const char* GetCategory() const override { return "Math"; }
    std::vector<ShaderPort> Inputs() const override;
    std::vector<ShaderPort> Outputs() const override;
    void Evaluate(const ShaderContext& ctx, const std::vector<ShaderValue>& inputs, std::vector<ShaderValue>& outputs) const override;
};

// Material: Outputs base material properties
class BaseColorNode : public ShaderNode {
public:
    const char* GetName() const override { return "BaseColor"; }
    const char* GetCategory() const override { return "Material"; }
    std::vector<ShaderPort> Inputs() const override;
    std::vector<ShaderPort> Outputs() const override;
    void Evaluate(const ShaderContext& ctx, const std::vector<ShaderValue>& inputs, std::vector<ShaderValue>& outputs) const override;
};

// Geometry: Provides UV coordinates from context
class UVCoordNode : public ShaderNode {
public:
    const char* GetName() const override { return "UVCoord"; }
    const char* GetCategory() const override { return "Geometry"; }
    std::vector<ShaderPort> Inputs() const override;
    std::vector<ShaderPort> Outputs() const override;
    void Evaluate(const ShaderContext& ctx, const std::vector<ShaderValue>& inputs, std::vector<ShaderValue>& outputs) const override;
};

}
