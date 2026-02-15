#pragma once

#include "ecs/entity.h"
#include <string>

namespace atlas {

class GalacticResponseSystem {
public:
    static void initialize(ecs::Entity* galaxy);
    static void update(ecs::Entity* galaxy, float titan_progress, float avg_sector_tension);
    static float getPerceivedThreat(ecs::Entity* galaxy);
    static bool isEmergencyActive(ecs::Entity* galaxy);
};

} // namespace atlas
