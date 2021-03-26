/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** SpeedApplicationSystem
*/

#include "SpeedApplicationSystem.hpp"

SpeedApplicationSystem::SpeedApplicationSystem()
{
    timeBeforeSend = 200;
}

SpeedApplicationSystem::~SpeedApplicationSystem()
{
}

void SpeedApplicationSystem::update(Coordinator &coordinator, Room &room, float const &timePassed)
{
    std::set<Entity> entities = coordinator.getEntities();

    timeBeforeSend -= timePassed;
    for (auto entity : entities) {
        if (coordinator.hasComponent<Speed>(entity) && coordinator.hasComponent<Position>(entity)) {
            Position &pos = coordinator.getComponent<Position>(entity);
            Speed &speed = coordinator.getComponent<Speed>(entity);
            pos.x += (speed.x * timePassed / 1000.0);
            pos.y += (speed.y * timePassed / 1000.0);
            if (coordinator.hasComponent<EntityType>(entity) && coordinator.getComponent<EntityType>(entity) == PLAYER) {
                if (pos.x < 15)
                    pos.x = 15;
                if (pos.y < 10)
                    pos.y = 10;
                if (pos.x > 840)
                    pos.x = 840;
                if (pos.y > 470)
                    pos.y = 470;
            }
            if (timeBeforeSend <= 0)
                Sender::sendComponents(coordinator, entity, {
                    {POSITION, pos},
                    {SPEED, speed},
                });
        }
    }
    if (timeBeforeSend <= 0)
        timeBeforeSend = 200;
}