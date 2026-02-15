#pragma once

#include "ecs/entity.h"
#include <string>
#include <vector>

namespace atlas {

class TradeFlowSystem {
public:
    static void initialize(ecs::Entity* market);
    static void addFlow(ecs::Entity* market, const std::string& item, float supply, float demand);
    static void update(ecs::Entity* market, float dt);
    static float getScarcityIndex(ecs::Entity* market);
    static float getPriceModifier(ecs::Entity* market, const std::string& item);
};

} // namespace atlas
