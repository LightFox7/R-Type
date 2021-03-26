/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** HandleInputSystem
*/

#include "HandleInputSystem.hpp"

HandleInputSystem::HandleInputSystem()
{
}

HandleInputSystem::~HandleInputSystem()
{
}

void HandleInputSystem::update(Coordinator &coordinator, Room &room)
{
    std::set<Entity> entities = coordinator.getEntities();

    for (auto entity : entities) {
        if (coordinator.hasComponent<PlayerId>(entity))
            applyToPlayer(coordinator, room, entity);
    }
}

void HandleInputSystem::applyToPlayer(Coordinator &coordinator, Room &room, Entity const &entity)
{
    Speed speed;

    if (!coordinator.hasComponent<Speed>(entity) || !coordinator.hasComponent<EntityType>(entity) || !coordinator.hasComponent<Position>(entity))
        return;
    EntityType &type = coordinator.getComponent<EntityType>(entity);
    if (type != PLAYER)
        return;
    for (auto it : room.clients) {
        if (it.getId() == coordinator.getComponent<PlayerId>(entity)) {
            if (it.actualInput.down)
                speed.y = 200;
            if (it.actualInput.up)
                speed.y = -200;
            if (it.actualInput.left)
                speed.x = -300;
            if (it.actualInput.right)
                speed.x = 400;
            if (speed.x != coordinator.getComponent<Speed>(entity).x || speed.y != coordinator.getComponent<Speed>(entity).y) {
                coordinator.addComponent<Speed>(entity, speed);
                Sender::sendComponents(coordinator, entity, {
                    {POSITION, coordinator.getComponent<Position>(entity)},
                    {SPEED, speed},
                });
            }
            if (it.actualInput.shoot) {
                Event shootEvent(Events::GENERATESHOT);
                shootEvent.SetParam<Entity>(Events::GenerateShot::SHOOTER, entity);
                coordinator.SendEvent(coordinator, shootEvent);
            }
        }
    }
}