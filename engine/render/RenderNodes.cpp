#include "RenderNodes.h"
#include <algorithm>

namespace atlas::render {

// --- ClearPassNode ---

std::vector<RenderPort> ClearPassNode::Inputs() const {
    return {
        {"ClearR", RenderPinType::Float},
        {"ClearG", RenderPinType::Float},
        {"ClearB", RenderPinType::Float},
        {"ClearA", RenderPinType::Float}
    };
}

std::vector<RenderPort> ClearPassNode::Outputs() const {
    return {{"ColorTarget", RenderPinType::Texture}};
}

void ClearPassNode::Evaluate(const RenderContext& ctx, const std::vector<RenderValue>& inputs, std::vector<RenderValue>& outputs) const {
    float r = (inputs.size() > 0 && !inputs[0].data.empty()) ? inputs[0].data[0] : 0.0f;
    float g = (inputs.size() > 1 && !inputs[1].data.empty()) ? inputs[1].data[0] : 0.0f;
    float b = (inputs.size() > 2 && !inputs[2].data.empty()) ? inputs[2].data[0] : 0.0f;
    float a = (inputs.size() > 3 && !inputs[3].data.empty()) ? inputs[3].data[0] : 1.0f;

    uint32_t pixelCount = ctx.width * ctx.height;
    outputs.resize(1);
    outputs[0].type = RenderPinType::Texture;
    outputs[0].tag = "cleared_color";
    outputs[0].data.resize(pixelCount * 4);

    for (uint32_t i = 0; i < pixelCount; ++i) {
        outputs[0].data[i * 4 + 0] = r;
        outputs[0].data[i * 4 + 1] = g;
        outputs[0].data[i * 4 + 2] = b;
        outputs[0].data[i * 4 + 3] = a;
    }
}

// --- GeometryPassNode ---

std::vector<RenderPort> GeometryPassNode::Inputs() const {
    return {
        {"ColorTarget", RenderPinType::Texture},
        {"Objects", RenderPinType::DrawList}
    };
}

std::vector<RenderPort> GeometryPassNode::Outputs() const {
    return {
        {"ColorOutput", RenderPinType::Texture},
        {"DepthOutput", RenderPinType::Texture}
    };
}

void GeometryPassNode::Evaluate(const RenderContext& ctx, const std::vector<RenderValue>& inputs, std::vector<RenderValue>& outputs) const {
    uint32_t pixelCount = ctx.width * ctx.height;

    outputs.resize(2);

    // ColorOutput: copy input color target or create default
    outputs[0].type = RenderPinType::Texture;
    outputs[0].tag = "geometry_color";
    if (!inputs.empty() && !inputs[0].data.empty()) {
        outputs[0].data = inputs[0].data;
    } else {
        outputs[0].data.resize(pixelCount * 4, 0.0f);
    }

    // DepthOutput: far plane (1.0f)
    outputs[1].type = RenderPinType::Texture;
    outputs[1].tag = "geometry_depth";
    outputs[1].data.resize(pixelCount, 1.0f);
}

// --- PostProcessNode ---

std::vector<RenderPort> PostProcessNode::Inputs() const {
    return {
        {"ColorInput", RenderPinType::Texture},
        {"Exposure", RenderPinType::Float}
    };
}

std::vector<RenderPort> PostProcessNode::Outputs() const {
    return {{"FinalColor", RenderPinType::Texture}};
}

void PostProcessNode::Evaluate(const RenderContext& ctx, const std::vector<RenderValue>& inputs, std::vector<RenderValue>& outputs) const {
    float exposure = 1.0f;
    if (inputs.size() > 1 && !inputs[1].data.empty()) {
        exposure = inputs[1].data[0];
    }

    uint32_t pixelCount = ctx.width * ctx.height;
    outputs.resize(1);
    outputs[0].type = RenderPinType::Texture;
    outputs[0].tag = "postprocess_color";

    if (!inputs.empty() && !inputs[0].data.empty()) {
        outputs[0].data = inputs[0].data;
        for (size_t i = 0; i < outputs[0].data.size(); ++i) {
            outputs[0].data[i] *= exposure;
        }
    } else {
        outputs[0].data.resize(pixelCount * 4, 0.0f);
    }
}

// --- PresentNode ---

std::vector<RenderPort> PresentNode::Inputs() const {
    return {{"FinalColor", RenderPinType::Texture}};
}

std::vector<RenderPort> PresentNode::Outputs() const {
    return {{"Swapchain", RenderPinType::Texture}};
}

void PresentNode::Evaluate(const RenderContext& ctx, const std::vector<RenderValue>& inputs, std::vector<RenderValue>& outputs) const {
    uint32_t pixelCount = ctx.width * ctx.height;
    outputs.resize(1);
    outputs[0].type = RenderPinType::Texture;
    outputs[0].tag = "swapchain";

    if (!inputs.empty() && !inputs[0].data.empty()) {
        outputs[0].data = inputs[0].data;
    } else {
        outputs[0].data.resize(pixelCount * 4, 0.0f);
    }
}

}
