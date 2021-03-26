/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Player
*/

#include "Player.hpp"

Entity Player::create(Coordinator &coordinator, PlayerId id, Position pos)
{
    Entity player = coordinator.createEntity();

    coordinator.addComponent<EntityType>(player, PLAYER);
    coordinator.addComponent<PlayerId>(player, id);
    coordinator.addComponent<Position>(player, pos);
    coordinator.addComponent<Speed>(player, {0, 0});
    coordinator.addComponent<HitBox>(player, {-16, -7, 32, 15});

    Sender::sendEntity(coordinator, player, PLAYER, id, {
        {POSITION, pos},
    });
    return player;
}