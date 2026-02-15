#pragma once

#include "ecs/entity.h"
#include <string>

namespace atlas {

/// NPC archetype-driven behavior selection.
/// Each NPC archetype has default intent preferences, equipment loadouts,
/// and risk profiles that influence how the NPC intent system selects actions.
class NPCArchetypeSystem {
public:
    /// Attach an NPCArchetype component to an NPC entity.
    /// @param npc       The NPC entity.
    /// @param archetype Archetype name (Trader, Pirate, Patrol, Miner, Hauler, Industrialist).
    static void initialize(ecs::Entity* npc, const std::string& archetype);

    /// Select the preferred intent for the NPC based on its archetype and
    /// the current star-system conditions.
    /// @param npc                 The NPC entity (must have NPCArchetype + NPCIntent).
    /// @param security            System security level (0-1).
    /// @param resource_availability Resource richness (0-1).
    /// @param threat_level        Current threat (0-1).
    static void selectArchetypeIntent(ecs::Entity* npc,
                                      float security,
                                      float resource_availability,
                                      float threat_level);

    /// Return a human-readable label for the NPC's archetype.
    static std::string getArchetypeName(ecs::Entity* npc);

    /// Return the archetype's base risk tolerance (0-1).
    static float getRiskTolerance(ecs::Entity* npc);
};

} // namespace atlas
