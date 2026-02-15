#pragma once

#include "ecs/world.h"
#include "ecs/entity.h"
#include <vector>
#include <string>

namespace atlas {

/**
 * @brief Server-side LOD culling for large battle optimisation
 *
 * Assigns LOD priority values to entities based on distance from an
 * observer (typically the player's ship).  Entities beyond a configurable
 * culling distance are marked as culled (priority 0, impostor candidates).
 * Player ships and explicitly flagged entities are never culled.
 *
 * Usage:
 *   LODCullingSystem::updatePriorities(world, observerX, observerY, observerZ);
 *   auto culled = LODCullingSystem::getCulledEntities(world);
 *   auto visible = LODCullingSystem::getVisibleEntities(world);
 */
class LODCullingSystem {
public:
    /// Recalculate LOD priorities for every entity that has both Position
    /// and LODPriority components.  Entities closer to the observer get a
    /// higher priority; entities beyond `cull_distance` are culled.
    static void updatePriorities(ecs::World* world,
                                 float observerX, float observerY, float observerZ,
                                 float cull_distance = 50000.0f);

    /// Return entities whose LODPriority is effectively culled (priority <= 0
    /// and not force_visible).
    static std::vector<ecs::Entity*> getCulledEntities(ecs::World* world);

    /// Return entities that should receive full-detail updates (not culled).
    static std::vector<ecs::Entity*> getVisibleEntities(ecs::World* world);

    /// Count how many entities are currently culled.
    static int getCulledCount(ecs::World* world);

    /// Count how many entities are visible (not culled).
    static int getVisibleCount(ecs::World* world);
};

} // namespace atlas
