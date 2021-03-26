/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** DestroySystem
*/

#include "DestroySystem.hpp"

DestroySystem::DestroySystem()
{
}

DestroySystem::~DestroySystem()
{
}

void DestroySystem::update(Coordinator &coordinator, Room &room, float const &timePassed)
{
    std::set<Entity> entities = coordinator.getEntities();

    for (auto entity : entities) {
        if (coordinator.hasComponent<EntityType>(entity) && coordinator.getComponent<EntityType>(entity) == SHOT)
            checkDestroyShot(coordinator, entity);
        if (coordinator.hasComponent<EntityType>(entity) && coordinator.getComponent<EntityType>(entity) == MONSTER)
            checkDestroyMonster(coordinator, entity);
        if (coordinator.hasComponent<Destroy>(entity)) {
            Destroy &destroy = coordinator.getComponent<Destroy>(entity);
            destroy -= timePassed;
            if (destroy <= 0)
                destroyEntity(coordinator, entity);
        }
    }
}

void DestroySystem::destroyEntity(Coordinator &coordinator, Entity const &entity)
{
    if (coordinator.hasComponent<EntityType>(entity) && coordinator.hasComponent<Position>(entity)) {
        EntityType type = coordinator.getComponent<EntityType>(entity);
        Position pos = coordinator.getComponent<Position>(entity);
        if (type == MONSTER && coordinator.hasComponent<DoExplode>(entity) && coordinator.getComponent<DoExplode>(entity).doexplode == true)
            Explosion::createExplosion(coordinator, MONSTEREXPLOSION1, pos);
        if (type == PLAYER)
            Explosion::createExplosion(coordinator, PLAYEREXPLOSION, pos);
    }
    coordinator.removeEntity(coordinator._room, entity);
}

void DestroySystem::checkDestroyShot(Coordinator &coordinator, Entity const &entity)
{
    if (!coordinator.hasComponent<Position>(entity))
        return;
    Position &pos = coordinator.getComponent<Position>(entity);
    if (pos.x > 2000 || pos.x < -50 || pos.y > 1200 || pos.y < -50)
        coordinator.addComponent<Destroy>(entity, 0);
}

void DestroySystem::checkDestroyMonster(Coordinator &coordinator, Entity const &entity)
{
    if (!coordinator.hasComponent<Position>(entity))
        return;
    Position &pos = coordinator.getComponent<Position>(entity);
    if (pos.x > 1100 || pos.x < -100 || pos.y > 750 || pos.y < -200)
        coordinator.addComponent<Destroy>(entity, 0);
}