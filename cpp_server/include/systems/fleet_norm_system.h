#pragma once

#include "ecs/entity.h"
#include <string>

namespace atlas {

class FleetNormSystem {
public:
    static void initialize(ecs::Entity* fleet);
    static void recordNormViolation(ecs::Entity* fleet);
    static void recordNormReinforcement(ecs::Entity* fleet);
    static float getNormStability(ecs::Entity* fleet);
    static void updateRiskAppetite(ecs::Entity* fleet, float recent_outcomes);
};

} // namespace atlas
