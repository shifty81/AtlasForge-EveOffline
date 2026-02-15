#include "ShaderNodes.h"

namespace atlas::shader {

// --- MultiplyNode ---

std::vector<ShaderPort> MultiplyNode::Inputs() const {
    return {
        {"A", ShaderPinType::Float},
        {"B", ShaderPinType::Float}
    };
}

std::vector<ShaderPort> MultiplyNode::Outputs() const {
    return {{"Result", ShaderPinType::Float}};
}

void MultiplyNode::Evaluate(const ShaderContext& ctx, const std::vector<ShaderValue>& inputs, std::vector<ShaderValue>& outputs) const {
    float a = 1.0f;
    float b = 1.0f;
    if (!inputs.empty() && !inputs[0].data.empty()) {
        a = inputs[0].data[0];
    }
    if (inputs.size() > 1 && !inputs[1].data.empty()) {
        b = inputs[1].data[0];
    }

    outputs.resize(1);
    outputs[0].type = ShaderPinType::Float;
    outputs[0].data = {a * b};
}

// --- LerpNode ---

std::vector<ShaderPort> LerpNode::Inputs() const {
    return {
        {"A", ShaderPinType::Vec3},
        {"B", ShaderPinType::Vec3},
        {"T", ShaderPinType::Float}
    };
}

std::vector<ShaderPort> LerpNode::Outputs() const {
    return {{"Result", ShaderPinType::Vec3}};
}

void LerpNode::Evaluate(const ShaderContext& ctx, const std::vector<ShaderValue>& inputs, std::vector<ShaderValue>& outputs) const {
    float ax = 0.0f, ay = 0.0f, az = 0.0f;
    float bx = 1.0f, by = 1.0f, bz = 1.0f;
    float t = 0.5f;

    if (!inputs.empty() && inputs[0].data.size() >= 3) {
        ax = inputs[0].data[0]; ay = inputs[0].data[1]; az = inputs[0].data[2];
    }
    if (inputs.size() > 1 && inputs[1].data.size() >= 3) {
        bx = inputs[1].data[0]; by = inputs[1].data[1]; bz = inputs[1].data[2];
    }
    if (inputs.size() > 2 && !inputs[2].data.empty()) {
        t = inputs[2].data[0];
    }

    outputs.resize(1);
    outputs[0].type = ShaderPinType::Vec3;
    outputs[0].data = {
        ax + (bx - ax) * t,
        ay + (by - ay) * t,
        az + (bz - az) * t
    };
}

// --- BaseColorNode ---

std::vector<ShaderPort> BaseColorNode::Inputs() const {
    return {
        {"Color", ShaderPinType::Vec3},
        {"Roughness", ShaderPinType::Float},
        {"Metallic", ShaderPinType::Float}
    };
}

std::vector<ShaderPort> BaseColorNode::Outputs() const {
    return {
        {"Albedo", ShaderPinType::Vec3},
        {"Roughness", ShaderPinType::Float},
        {"Metallic", ShaderPinType::Float}
    };
}

void BaseColorNode::Evaluate(const ShaderContext& ctx, const std::vector<ShaderValue>& inputs, std::vector<ShaderValue>& outputs) const {
    float cr = 0.8f, cg = 0.8f, cb = 0.8f;
    float roughness = 0.5f;
    float metallic = 0.0f;

    if (!inputs.empty() && inputs[0].data.size() >= 3) {
        cr = inputs[0].data[0]; cg = inputs[0].data[1]; cb = inputs[0].data[2];
    }
    if (inputs.size() > 1 && !inputs[1].data.empty()) {
        roughness = inputs[1].data[0];
    }
    if (inputs.size() > 2 && !inputs[2].data.empty()) {
        metallic = inputs[2].data[0];
    }

    outputs.resize(3);
    outputs[0].type = ShaderPinType::Vec3;
    outputs[0].data = {cr, cg, cb};
    outputs[1].type = ShaderPinType::Float;
    outputs[1].data = {roughness};
    outputs[2].type = ShaderPinType::Float;
    outputs[2].data = {metallic};
}

// --- UVCoordNode ---

std::vector<ShaderPort> UVCoordNode::Inputs() const {
    return {};
}

std::vector<ShaderPort> UVCoordNode::Outputs() const {
    return {{"UV", ShaderPinType::Vec2}};
}

void UVCoordNode::Evaluate(const ShaderContext& ctx, const std::vector<ShaderValue>& inputs, std::vector<ShaderValue>& outputs) const {
    outputs.resize(1);
    outputs[0].type = ShaderPinType::Vec2;
    outputs[0].data = {ctx.u, ctx.v};
}

}
