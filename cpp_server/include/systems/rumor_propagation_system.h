#pragma once

#include "ecs/entity.h"
#include <string>

namespace atlas {

class RumorPropagationSystem {
public:
    static void initialize(ecs::Entity* captain);
    static void propagateRumor(ecs::Entity* source, ecs::Entity* target, const std::string& rumor_id);
    static int getRumorCount(ecs::Entity* captain);
    static float getRumorBelief(ecs::Entity* captain, const std::string& rumor_id);
};

} // namespace atlas
