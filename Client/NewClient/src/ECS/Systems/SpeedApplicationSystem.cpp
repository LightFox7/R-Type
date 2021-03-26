/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** SpeedApplicationSystem
*/

#include "SpeedApplicationSystem.hpp"

SpeedApplicationSystem::SpeedApplicationSystem()
{
}

SpeedApplicationSystem::~SpeedApplicationSystem()
{
}

void SpeedApplicationSystem::update(Coordinator &coordinator, float const &timePassed)
{
    std::set<Entity> entities = coordinator.getEntities();

    for (auto entity : entities) {
        if (coordinator.hasComponent<Speed>(entity) && coordinator.hasComponent<Position>(entity)) {
            Position &pos = coordinator.getComponent<Position>(entity);
            Speed &speed = coordinator.getComponent<Speed>(entity);
            pos.x += (speed.x * timePassed / 1000.0);
            pos.y += (speed.y * timePassed / 1000.0);
        }
    }
}