/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** GenerateShotSystem
*/

#include "GenerateShotSystem.hpp"

GenerateShotSystem::GenerateShotSystem(Coordinator &coordinator)
{
    coordinator.AddEventListener(METHOD_LISTENER(Events::GENERATESHOT, GenerateShotSystem::createShot));
}

GenerateShotSystem::~GenerateShotSystem()
{
}

void GenerateShotSystem::createShot(Coordinator &coordinator, Event &event)
{
    Entity entity = event.GetParam<Entity>(Events::GenerateShot::SHOOTER);
    EntityType type;

    if (coordinator.hasComponent<EntityType>(entity)) {
        type = coordinator.getComponent<EntityType>(entity);
        if (type == PLAYER)
            createShotPlayer(coordinator, entity);
    }
}

void GenerateShotSystem::createShotPlayer(Coordinator &coordinator, Entity const &entity)
{
    Position pos;

    if (!coordinator.hasComponent<Position>(entity))
        return;
    pos = coordinator.getComponent<Position>(entity);
    PlayerShot::createLittle(coordinator, {pos.x + 15, pos.y});
}
