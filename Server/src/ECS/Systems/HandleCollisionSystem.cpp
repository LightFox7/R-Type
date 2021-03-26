/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** ColisionSystem
*/

#include "HandleCollisionSystem.hpp"

HandleCollisionSystem::HandleCollisionSystem(Coordinator &coordinator)
{
    coordinator.AddEventListener(METHOD_LISTENER(Events::COLLIDE, HandleCollisionSystem::handleCollision));
}

HandleCollisionSystem::~HandleCollisionSystem()
{
}

void HandleCollisionSystem::update(Coordinator &coordinator, Room &room) {
    std::set<Entity> entities  = coordinator.getEntities();

    for (auto it1 = entities.begin(); it1 != entities.end(); ++it1) {
        auto it2 = it1;
        ++it2;
        if (it2 == entities.end())
            break;
        for (; it2 != entities.end(); ++it2) {
            if (coordinator.hasComponent<HitBox>(*it1) && coordinator.hasComponent<HitBox>(*it2)
            && coordinator.hasComponent<Position>(*it1) && coordinator.hasComponent<Position>(*it2))
                collideTwoEntities(coordinator, *it1, *it2);
        }
    }
}

void HandleCollisionSystem::collideTwoEntities(Coordinator &coordinator, Entity const &entity1, Entity const &entity2)
{
    Position &pos1 = coordinator.getComponent<Position>(entity1);
    Position &pos2 = coordinator.getComponent<Position>(entity2);
    HitBox &hitbox1 = coordinator.getComponent<HitBox>(entity1);
    HitBox &hitbox2 = coordinator.getComponent<HitBox>(entity2);

    if (checkCollision(pos1, hitbox1, pos2, hitbox2)) {
        Event collideEvent(Events::COLLIDE);
        collideEvent.SetParam<Entity>(Events::Collide::ENTITY1, entity1);
        collideEvent.SetParam<Entity>(Events::Collide::ENTITY2, entity2);
        coordinator.SendEvent(coordinator, collideEvent);
        collideEvent.SetParam<Entity>(Events::Collide::ENTITY1, entity2);
        collideEvent.SetParam<Entity>(Events::Collide::ENTITY2, entity1);
        coordinator.SendEvent(coordinator, collideEvent);
    }
}

bool HandleCollisionSystem::checkCollision(Position const &pos1, HitBox &hitbox1, Position &pos2, HitBox &hitbox2)
{
    if (((pos2.x + hitbox2.offsetx) >= ((pos1.x + hitbox1.offsetx) + hitbox1.width))
        || (((pos2.x + hitbox2.offsetx) + hitbox2.width) <= (pos1.x + hitbox1.offsetx))
        || ((pos2.y + hitbox2.offsety) >= ((pos1.y + hitbox1.offsety) + hitbox1.height))
        || (((pos2.y + hitbox2.offsety) + hitbox2.height) <= (pos1.y + hitbox1.offsety)))
        return (false);
    else
        return (true);
}

void HandleCollisionSystem::handleCollision(Coordinator &coordinator, Event &event)
{
    Entity entity1 = event.GetParam<Entity>(Events::Collide::ENTITY1);
    Entity entity2 = event.GetParam<Entity>(Events::Collide::ENTITY2);

    EntityType type1 = coordinator.getComponent<EntityType>(entity1);
    EntityType type2 = coordinator.getComponent<EntityType>(entity2);

    if (type1 == PLAYER)
        PlayerCollision(coordinator, entity1, type1, entity2, type2);
    else if (type1 == MONSTER)
        MonsterCollision(coordinator, entity1, type1, entity2, type2);
    else if (type1 == SHOT)
        ShotCollision(coordinator, entity1, type1, entity2, type2);
}

void HandleCollisionSystem::WallCollision(Coordinator &coordinator, Entity const &entity1, EntityType const &type1, Entity const &entity2, EntityType const &type2)
{
    if (type2 == PLAYER) {
        return;
    }
    else if (type2 == MONSTER) {
        return;
    }
}

void HandleCollisionSystem::ShotCollision(Coordinator &coordinator, Entity const &entity1, EntityType const &type1, Entity const &entity2, EntityType const &type2)
{
    if (type2 == PLAYER) {
        return;
    }
    else if (type2 == MONSTER) {
        if (!coordinator.hasComponent<ShotController>(entity1))
            return;
        ShotController &shotController = coordinator.getComponent<ShotController>(entity1);
        if (!shotController.pierce)
            coordinator.addComponent<Destroy>(entity1, 0);
        return;
    }
}

void HandleCollisionSystem::PlayerCollision(Coordinator &coordinator, Entity const &entity1, EntityType const &type1, Entity const &entity2, EntityType const &type2)
{
    if (type2 == MONSTER) {
        coordinator.addComponent<Destroy>(entity1, 0);
    }
    else if (type2 == WALL) {
    }
}

void HandleCollisionSystem::MonsterCollision(Coordinator &coordinator, Entity const &entity1, EntityType const &type1, Entity const &entity2, EntityType const &type2)
{
    if (type2 == PLAYER) {
    }
    else if (type2 == WALL) {
        return;
    }
    else if (type2 == SHOT) {
        if (!coordinator.hasComponent<Health>(entity1) || !coordinator.hasComponent<ShotController>(entity2))
            return;
        Health &monsterHealth = coordinator.getComponent<Health>(entity1);
        ShotController &shotController = coordinator.getComponent<ShotController>(entity2);
        if (shotController.hasHit.find(entity1) == shotController.hasHit.end())
            monsterHealth -= shotController.damage;
        if (monsterHealth <= 0) {
            coordinator.addComponent<Destroy>(entity1, 0);
            coordinator.addComponent<DoExplode>(entity1, {true});
        }
    }
}