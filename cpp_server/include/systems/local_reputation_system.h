#pragma once

#include "ecs/entity.h"
#include <string>

namespace atlas {

/// Per-system local reputation tracking.
/// Each star system maintains independent reputation scores for entities,
/// allowing the same player/NPC to have different standings in different systems.
class LocalReputationSystem {
public:
    /// Add a LocalReputation component to an entity with default values.
    static void initialize(ecs::Entity* entity);

    /// Modify an entity's reputation in a specific star system.
    /// @param entity      Entity whose local reputation is being changed.
    /// @param system_name Name of the star system.
    /// @param change      Reputation delta (can be negative).
    static void modifyReputation(ecs::Entity* entity,
                                 const std::string& system_name,
                                 float change);

    /// Query an entity's reputation in a specific star system.
    /// @return Reputation value clamped to [-10, 10], or 0 if no record.
    static float getReputation(ecs::Entity* entity,
                               const std::string& system_name);

    /// Decay all reputation values toward zero by a fixed rate per tick.
    /// @param entity Entity whose reputations decay.
    /// @param dt     Delta time in seconds.
    static void decayReputations(ecs::Entity* entity, float dt);

    /// Check whether the entity has positive standing in a system.
    static bool isWelcome(ecs::Entity* entity,
                          const std::string& system_name);
};

} // namespace atlas
