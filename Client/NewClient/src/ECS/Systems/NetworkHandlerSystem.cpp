/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** NetworkHandlerSystem
*/

#include "NetworkHandlerSystem.hpp"

NetworkHandlerSystem::NetworkHandlerSystem()
{
}

NetworkHandlerSystem::~NetworkHandlerSystem()
{
}

void NetworkHandlerSystem::update(Coordinator &coordinator, Core &core, std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators)
{
    Response::ResponseStruct response;

    while (core.listCommand.begin() != core.listCommand.end()) {
        response = core.listCommand.front();
        core.listCommand.pop_front();
        if (response.code == Response::GameCode::CreateEntity)
            createEntity(coordinator, response, monsterCreators);
        if (response.code == Response::GameCode::DeleteEntity)
            deleteEntity(coordinator, response);
        if (response.code == Response::GameCode::SetComponent)
            createComponent(coordinator, response);
    }
}

void NetworkHandlerSystem::createEntity(Coordinator &coordinator, Response::ResponseStruct &response, std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators)
{
    int offset = 0;

    Entity id = *(Entity *)(response.event + offset);
    offset += sizeof(Entity);
    EntityType type = *(EntityType *)(response.event + offset);
    offset += sizeof(EntityType);
    if (type == PLAYER) {
        PlayerId playerId = *(PlayerId *)(response.event + offset);
        offset += sizeof(PlayerId);
        Player::create(coordinator, id, playerId);
    }
    else if (type == MONSTER) {
        MonsterType monsterType = *(MonsterType *)(response.event + offset);
        offset += sizeof(MonsterType);
        for (auto it : monsterCreators)
            if (it.first == monsterType) {
                createMonster(coordinator, it.second->create(), id);
            }
    }
    else if (type == SHOT) {
        ShotType shotType = *(ShotType *)(response.event + offset);
        offset += sizeof(ShotType);
        if (shotType == LITTLESHOT)
            PlayerShot::createLittle(coordinator, id);
        else if (shotType == CHARGEDSHOT)
            PlayerShot::createCharged(coordinator, id);
    }
    else if (type == EXPLOSION) {
        ExplosionType explostionType = *(ExplosionType *)(response.event + offset);
        offset += sizeof(ExplosionType);
        Explosion::createExplosion(coordinator, id, explostionType);
    }
    ComponentType componentType;
    while ((componentType = *(ComponentType *)(response.event + offset)) != 0) {
        offset += sizeof(ComponentType);
        if (componentType == SPEED) {
            coordinator.addComponent<Speed>(id, *(Speed *)(response.event + offset));
            offset += sizeof(Speed);
        }
        if (componentType == POSITION) {
            coordinator.addComponent<Position>(id, *(Position *)(response.event + offset));
            offset += sizeof(Position);
        }
    }
}

void NetworkHandlerSystem::createMonster(Coordinator &coordinator, std::map<ComponentType, std::any> const &components, Entity const &id)
{
    Entity monster = coordinator.createEntity(id);

    for (auto const &it: components) {
        coordinator.addComponent(monster, it.first, it.second);
    }
}

void NetworkHandlerSystem::deleteEntity(Coordinator &coordinator, Response::ResponseStruct &response)
{
    int offset = 0;

    Entity id = *(Entity *)(response.event + offset);
    offset += sizeof(Entity);
    coordinator.removeEntity(id);
}

void NetworkHandlerSystem::createComponent(Coordinator &coordinator, Response::ResponseStruct &response)
{
    int offset = 0;
    ComponentType type;

    Entity entity = *(Entity *)(response.event + offset);
    offset += sizeof(Entity);
    while ((type = *(ComponentType *)(response.event + offset)) != 0) {
        offset += sizeof(ComponentType);
        if (type == SPEED) {
            coordinator.addComponent<Speed>(entity, *(Speed *)(response.event + offset));
            offset += sizeof(Speed);
        }
        if (type == POSITION) {
            coordinator.addComponent<Position>(entity, *(Position *)(response.event + offset));
            offset += sizeof(Position);
        }
    }
}