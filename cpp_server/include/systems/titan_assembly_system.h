#pragma once

#include "ecs/entity.h"

namespace atlas {

class TitanAssemblySystem {
public:
    static void initialize(ecs::Entity* titan);
    static void update(ecs::Entity* titan, float dt, float logistics_health);
    static float getOverallProgress(ecs::Entity* titan);
    static float getResourcePressure(ecs::Entity* titan);
    static bool isComplete(ecs::Entity* titan);
};

} // namespace atlas
