#pragma once

#include "ecs/entity.h"
#include <string>

namespace atlas {

class NPCIntentSystem {
public:
    static void initialize(ecs::Entity* npc);
    static void selectIntent(ecs::Entity* npc, float security, float resource_availability, float threat_level);
    static std::string getIntentName(ecs::Entity* npc);
    static float getIntentDuration(ecs::Entity* npc);
};

} // namespace atlas
