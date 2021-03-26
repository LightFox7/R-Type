/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Sender
*/

#include "Sender.hpp"

void Sender::sendEntity(Coordinator &coordinator, Entity const &entity, EntityType const &type, std::any id, std::map<ComponentType, std::any> components)
{
    Response::ResponseStruct response{};
    int offset = 0;

    response.code = Response::GameCode::CreateEntity;
    response.roomId = coordinator._room.getRoomId();
    std::memset(response.event, 0, sizeof(response.event));
    std::memcpy(response.event + offset, &entity, sizeof(Entity));
    offset += sizeof(Entity);
    std::memcpy(response.event + offset, &type, sizeof(EntityType));
    offset += sizeof(EntityType);
    if (type == PLAYER) {
        PlayerId playerId = std::any_cast<PlayerId>(id);
        std::memcpy(response.event + offset, &(playerId), sizeof(PlayerId));
        offset += sizeof(PlayerId);
    }
    else if (type == SHOT) {
        ShotType shotType = std::any_cast<ShotType>(id);
        std::memcpy(response.event + offset, &(shotType), sizeof(ShotType));
        offset += sizeof(ShotType);
    }
    else if (type == MONSTER) {
        MonsterType monsterType = std::any_cast<MonsterType>(id);
        std::memcpy(response.event + offset, &(monsterType), sizeof(MonsterType));
        offset += sizeof(MonsterType);
    }
    else if (type == EXPLOSION) {
        ExplosionType explosionType = std::any_cast<ExplosionType>(id);
        std::memcpy(response.event + offset, &(explosionType), sizeof(ExplosionType));
        offset += sizeof(ExplosionType);
    }
    for (auto const &it: components) {
        ComponentType componentType = it.first;
        if (offset > 40)
            break;
        std::memcpy(response.event + offset, &componentType, sizeof(ComponentType));
        offset += sizeof(ComponentType);
        if (componentType == POSITION) {
            Position pos = std::any_cast<Position>(it.second);
            std::memcpy(response.event + offset, &pos, sizeof(Position));
            offset += sizeof(Position);
        }
        else if (componentType == SPEED) {
            Speed speed = std::any_cast<Speed>(it.second);
            std::memcpy(response.event + offset, &speed, sizeof(Speed));
            offset += sizeof(Speed);
        }
    }
    coordinator._room.send_to_all(response);
}

void Sender::sendComponents(Coordinator &coordinator, Entity const &entity, std::map<ComponentType, std::any> toSend)
{
    Response::ResponseStruct response{};
    int offset = 0;

    response.code = Response::GameCode::SetComponent;
    response.roomId = coordinator._room.getRoomId();
    std::memset(response.event, 0, sizeof(response.event));
    std::memcpy(response.event + offset, &entity, sizeof(Entity));
    offset += sizeof(Entity);

    for (auto const &it: toSend) {
        ComponentType componentType = it.first;
        if (offset > 40)
            break;
        std::memcpy(response.event + offset, &componentType, sizeof(ComponentType));
        offset += sizeof(ComponentType);
        if (componentType == POSITION) {
            Position pos = std::any_cast<Position>(it.second);
            std::memcpy(response.event + offset, &pos, sizeof(Position));
            offset += sizeof(Position);
        }
        else if (componentType == SPEED) {
            Speed speed = std::any_cast<Speed>(it.second);
            std::memcpy(response.event + offset, &speed, sizeof(Speed));
            offset += sizeof(Speed);
        }
    }
    coordinator._room.send_to_all(response);
}

void Sender::sendDestroyEntity(Coordinator &coordinator, Entity const &entity)
{
    Response::ResponseStruct response{};

    response.code = Response::GameCode::DeleteEntity;
    response.roomId = coordinator._room.getRoomId();
    std::memset(response.event, 0, sizeof(response.event));
    std::memcpy(response.event, &entity, sizeof(Entity));
    coordinator._room.send_to_all(response);
}