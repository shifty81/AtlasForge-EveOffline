#include "systems/titan_assembly_system.h"
#include "components/game_components.h"

namespace atlas {

using namespace components;

void TitanAssemblySystem::initialize(ecs::Entity* titan) {
    if (!titan->hasComponent<TitanAssemblyProgress>()) {
        auto progress = std::make_unique<TitanAssemblyProgress>();

        const char* node_names[] = {
            "Superstructure Spine",
            "Primary Reactor Core",
            "Warp Field Projector",
            "Command Nexus",
            "Armor Lattice",
            "Weapon Mount Superframes"
        };

        for (const auto& name : node_names) {
            TitanAssemblyProgress::AssemblyNode node;
            node.name = name;
            node.completion = 0.0f;
            node.resource_debt = 1.0f;
            node.workforce_skill = 0.5f;
            node.concealment = 1.0f;
            progress->nodes.push_back(node);
        }

        titan->addComponent(std::move(progress));
    }
}

void TitanAssemblySystem::update(ecs::Entity* titan, float dt, float logistics_health) {
    auto* progress = titan->getComponent<TitanAssemblyProgress>();
    if (!progress) return;

    float completion_sum = 0.0f;

    for (auto& node : progress->nodes) {
        float advance = dt * 0.001f * logistics_health * node.workforce_skill;
        node.completion += advance;
        if (node.completion > 1.0f) node.completion = 1.0f;

        node.resource_debt -= advance;
        if (node.resource_debt < 0.0f) node.resource_debt = 0.0f;

        completion_sum += node.completion;
    }

    if (!progress->nodes.empty()) {
        progress->overall_progress = completion_sum / static_cast<float>(progress->nodes.size());
    }
}

float TitanAssemblySystem::getOverallProgress(ecs::Entity* titan) {
    auto* progress = titan->getComponent<TitanAssemblyProgress>();
    return progress ? progress->overall_progress : 0.0f;
}

float TitanAssemblySystem::getResourcePressure(ecs::Entity* titan) {
    auto* progress = titan->getComponent<TitanAssemblyProgress>();
    if (!progress || progress->nodes.empty()) return 0.0f;

    float pressure_sum = 0.0f;
    for (const auto& node : progress->nodes) {
        pressure_sum += (1.0f - node.completion) * node.resource_debt;
    }
    return pressure_sum / static_cast<float>(progress->nodes.size());
}

bool TitanAssemblySystem::isComplete(ecs::Entity* titan) {
    auto* progress = titan->getComponent<TitanAssemblyProgress>();
    return progress && progress->overall_progress >= 0.99f;
}

} // namespace atlas
