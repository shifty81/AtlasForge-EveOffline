#pragma once

#include "ecs/entity.h"
#include <string>

namespace atlas {

class SectorTensionSystem {
public:
    static void initialize(ecs::Entity* system);
    static void update(ecs::Entity* system, float dt, float pirate_activity, float trade_activity);
    static float getThreatLevel(ecs::Entity* system);
    static bool isUnderStress(ecs::Entity* system);
};

} // namespace atlas
