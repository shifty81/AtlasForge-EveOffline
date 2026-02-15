#include "systems/pirate_doctrine_system.h"
#include "components/game_components.h"

namespace atlas {

using namespace components;

void PirateDoctrineSystem::initialize(ecs::Entity* faction) {
    if (!faction->hasComponent<PirateDoctrine>()) {
        auto doctrine = std::make_unique<PirateDoctrine>();
        doctrine->doctrine = PirateDoctrineState::Accumulate;
        faction->addComponent(std::move(doctrine));
    }
}

void PirateDoctrineSystem::update(ecs::Entity* faction, float titan_progress, float discovery_risk) {
    auto* doctrine = faction->getComponent<PirateDoctrine>();
    if (!doctrine) return;

    if (titan_progress < 0.2f) {
        doctrine->doctrine = PirateDoctrineState::Accumulate;
        doctrine->aggression_level = 0.1f;
        doctrine->coordination = 0.2f;
    } else if (titan_progress < 0.5f) {
        if (discovery_risk > 0.5f) {
            doctrine->doctrine = PirateDoctrineState::Conceal;
            doctrine->aggression_level = 0.2f;
            doctrine->coordination = 0.5f;
        } else {
            doctrine->doctrine = PirateDoctrineState::Disrupt;
            doctrine->aggression_level = 0.5f;
            doctrine->coordination = 0.4f;
        }
    } else if (titan_progress < 0.8f) {
        doctrine->doctrine = PirateDoctrineState::Defend;
        doctrine->aggression_level = 0.7f;
        doctrine->coordination = 0.7f;
    } else {
        doctrine->doctrine = PirateDoctrineState::PrepareLaunch;
        doctrine->aggression_level = 1.0f;
        doctrine->coordination = 1.0f;
    }

    doctrine->discovery_risk = discovery_risk;
}

std::string PirateDoctrineSystem::getDoctrineName(ecs::Entity* faction) {
    auto* doctrine = faction->getComponent<PirateDoctrine>();
    if (!doctrine) return "None";

    switch (doctrine->doctrine) {
        case PirateDoctrineState::Accumulate:    return "Accumulate";
        case PirateDoctrineState::Conceal:       return "Conceal";
        case PirateDoctrineState::Disrupt:       return "Disrupt";
        case PirateDoctrineState::Defend:        return "Defend";
        case PirateDoctrineState::PrepareLaunch: return "PrepareLaunch";
        default:                                 return "Unknown";
    }
}

float PirateDoctrineSystem::getAggressionLevel(ecs::Entity* faction) {
    auto* doctrine = faction->getComponent<PirateDoctrine>();
    return doctrine ? doctrine->aggression_level : 0.0f;
}

} // namespace atlas
