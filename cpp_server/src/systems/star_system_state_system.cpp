#include "systems/star_system_state_system.h"
#include "components/game_components.h"
#include <algorithm>

namespace atlas {

using namespace components;

void StarSystemStateSystem::initialize(ecs::Entity* system) {
    if (!system->hasComponent<StarSystemState>()) {
        system->addComponent(std::make_unique<StarSystemState>());
    }
}

void StarSystemStateSystem::update(ecs::Entity* system, float dt,
                                    float npc_traffic, float mining_output,
                                    float pirate_activity) {
    auto* state = system->getComponent<StarSystemState>();
    if (!state) return;

    // Traffic tracks NPC/player ship activity with smoothing
    state->traffic += (npc_traffic - state->traffic) * 0.1f * dt;
    state->traffic = std::clamp(state->traffic, 0.0f, 1.0f);

    // Economy improves with mining output, degrades with pirate activity
    float economy_delta = (mining_output * 0.1f - pirate_activity * 0.15f) * dt;
    state->economy += economy_delta;
    state->economy = std::clamp(state->economy, 0.0f, 1.0f);

    // Security inversely related to pirate activity
    state->security = std::clamp(1.0f - pirate_activity * 0.8f, 0.0f, 1.0f);

    // Threat is a combination of pirate activity and low security
    state->threat = std::clamp(pirate_activity * 0.6f + (1.0f - state->security) * 0.4f, 0.0f, 1.0f);

    // Pirate spawn pressure rises when threat is high
    if (state->threat > 0.5f) {
        state->pirate_spawn_pressure += (state->threat - 0.5f) * dt * 0.1f;
    } else {
        state->pirate_spawn_pressure -= 0.05f * dt;
    }
    state->pirate_spawn_pressure = std::clamp(state->pirate_spawn_pressure, 0.0f, 1.0f);

    // Shortage severity rises when economy is low
    if (state->economy < 0.3f) {
        state->shortage_severity += (0.3f - state->economy) * dt * 0.2f;
    } else {
        state->shortage_severity -= 0.03f * dt;
    }
    state->shortage_severity = std::clamp(state->shortage_severity, 0.0f, 1.0f);

    // Lockdown triggers when threat exceeds threshold
    state->lockdown = state->threat > 0.8f;

    // Faction influence erodes under sustained pirate pressure
    if (pirate_activity > 0.6f) {
        state->faction_influence -= (pirate_activity - 0.6f) * dt * 0.05f;
    } else {
        state->faction_influence += 0.01f * dt;
    }
    state->faction_influence = std::clamp(state->faction_influence, 0.0f, 1.0f);
}

float StarSystemStateSystem::getSecurity(ecs::Entity* system) {
    auto* state = system->getComponent<StarSystemState>();
    return state ? state->security : 0.5f;
}

float StarSystemStateSystem::getEconomy(ecs::Entity* system) {
    auto* state = system->getComponent<StarSystemState>();
    return state ? state->economy : 0.5f;
}

float StarSystemStateSystem::getThreat(ecs::Entity* system) {
    auto* state = system->getComponent<StarSystemState>();
    return state ? state->threat : 0.0f;
}

bool StarSystemStateSystem::isLockdown(ecs::Entity* system) {
    auto* state = system->getComponent<StarSystemState>();
    return state ? state->lockdown : false;
}

} // namespace atlas
