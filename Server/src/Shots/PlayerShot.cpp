/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** PlayerShot
*/

#include "PlayerShot.hpp"

Entity PlayerShot::createLittle(Coordinator &coordinator, Position pos)
{
    Entity entity = coordinator.createEntity();

    coordinator.addComponent<EntityType>(entity, SHOT);
    coordinator.addComponent<Position>(entity, pos);
    coordinator.addComponent<Speed>(entity, {700, 0});
    coordinator.addComponent<HitBox>(entity, {-15, -5, 30, 10});
    coordinator.addComponent<ShotType>(entity, LITTLESHOT);
    coordinator.addComponent<ShotController>(entity, {10, false, std::set<Entity>()});
    Sender::sendEntity(coordinator, entity, SHOT, LITTLESHOT, {
        {POSITION, coordinator.getComponent<Position>(entity)},
        {SPEED, coordinator.getComponent<Speed>(entity)},
    });
    return entity;
}

Entity PlayerShot::createCharged(Coordinator &coordinator, Position pos)
{
    Entity entity = coordinator.createEntity();

    coordinator.addComponent<EntityType>(entity, SHOT);
    coordinator.addComponent<Position>(entity, pos);
    coordinator.addComponent<Speed>(entity, {600, 0});
    coordinator.addComponent<HitBox>(entity, {-2, -2, 5, 5});
    coordinator.addComponent<ShotType>(entity, LITTLESHOT);
    coordinator.addComponent<ShotController>(entity, {30, true, std::set<Entity>()});
    Sender::sendEntity(coordinator, entity, SHOT, LITTLESHOT, {
        {POSITION, coordinator.getComponent<Position>(entity)},
        {SPEED, coordinator.getComponent<Speed>(entity)},
    });
    return entity;
}