#pragma once

#include "ecs/entity.h"
#include <string>

namespace atlas {

class PirateDoctrineSystem {
public:
    static void initialize(ecs::Entity* faction);
    static void update(ecs::Entity* faction, float titan_progress, float discovery_risk);
    static std::string getDoctrineName(ecs::Entity* faction);
    static float getAggressionLevel(ecs::Entity* faction);
};

} // namespace atlas
