#pragma once
#include "RenderGraph.h"

namespace atlas::render {

// Produces a cleared color texture at the specified resolution
class ClearPassNode : public RenderNode {
public:
    const char* GetName() const override { return "ClearPass"; }
    const char* GetCategory() const override { return "Setup"; }
    std::vector<RenderPort> Inputs() const override;
    std::vector<RenderPort> Outputs() const override;
    void Evaluate(const RenderContext& ctx, const std::vector<RenderValue>& inputs, std::vector<RenderValue>& outputs) const override;
};

// Takes a texture and produces a depth-tested geometry pass output
class GeometryPassNode : public RenderNode {
public:
    const char* GetName() const override { return "GeometryPass"; }
    const char* GetCategory() const override { return "Core"; }
    std::vector<RenderPort> Inputs() const override;
    std::vector<RenderPort> Outputs() const override;
    void Evaluate(const RenderContext& ctx, const std::vector<RenderValue>& inputs, std::vector<RenderValue>& outputs) const override;
};

// Post-processing pass (applies simple tonemap to color texture)
class PostProcessNode : public RenderNode {
public:
    const char* GetName() const override { return "PostProcess"; }
    const char* GetCategory() const override { return "Effect"; }
    std::vector<RenderPort> Inputs() const override;
    std::vector<RenderPort> Outputs() const override;
    void Evaluate(const RenderContext& ctx, const std::vector<RenderValue>& inputs, std::vector<RenderValue>& outputs) const override;
};

// Final output / present pass
class PresentNode : public RenderNode {
public:
    const char* GetName() const override { return "Present"; }
    const char* GetCategory() const override { return "Output"; }
    std::vector<RenderPort> Inputs() const override;
    std::vector<RenderPort> Outputs() const override;
    void Evaluate(const RenderContext& ctx, const std::vector<RenderValue>& inputs, std::vector<RenderValue>& outputs) const override;
};

}
