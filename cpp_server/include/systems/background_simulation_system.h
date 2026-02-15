#pragma once

#include "ecs/entity.h"

namespace atlas {

class BackgroundSimulationSystem {
public:
    static void initialize(ecs::Entity* galaxy);
    static void update(ecs::Entity* galaxy, float dt);
    static float getSimTime(ecs::Entity* galaxy);
    static int getTotalTicks(ecs::Entity* galaxy);
    static void pause(ecs::Entity* galaxy);
    static void resume(ecs::Entity* galaxy);
};

} // namespace atlas
