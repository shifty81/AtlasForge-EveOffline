#pragma once

#include "ecs/entity.h"
#include <string>

namespace atlas {

class OperationalWearSystem {
public:
    static void initialize(ecs::Entity* ship);
    static void update(ecs::Entity* ship, float dt);
    static void dock(ecs::Entity* ship);
    static void fieldRepair(ecs::Entity* ship);
    static float getEfficiencyPenalty(ecs::Entity* ship);
    static bool needsDocking(ecs::Entity* ship);
};

} // namespace atlas
