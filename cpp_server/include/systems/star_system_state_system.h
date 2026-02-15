#pragma once

#include "ecs/entity.h"
#include <string>

namespace atlas {

class StarSystemStateSystem {
public:
    /// Add a StarSystemState component to a system entity with default values.
    static void initialize(ecs::Entity* system);

    /// Update the star system state based on observed activity levels.
    /// @param system      Entity representing the star system.
    /// @param dt          Delta time in seconds.
    /// @param npc_traffic Current NPC traffic activity (0-1).
    /// @param mining_output Current mining production rate (0-1).
    /// @param pirate_activity Current pirate presence (0-1).
    static void update(ecs::Entity* system, float dt,
                       float npc_traffic, float mining_output,
                       float pirate_activity);

    /// Query the effective security level.
    static float getSecurity(ecs::Entity* system);

    /// Query the economic health.
    static float getEconomy(ecs::Entity* system);

    /// Query the aggregate threat level.
    static float getThreat(ecs::Entity* system);

    /// Check whether the system has entered lockdown.
    static bool isLockdown(ecs::Entity* system);
};

} // namespace atlas
