/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Explosion
*/

#include "Explosion.hpp"

void Explosion::createExplosion(Coordinator &coordinator, ExplosionType const &type, Position pos)
{
    Entity entity = coordinator.createEntity();

    coordinator.addComponent<EntityType>(entity, EXPLOSION);
    coordinator.addComponent<ExplosionType>(entity, type);
    coordinator.addComponent<Position>(entity, pos);
    coordinator.addComponent<Speed>(entity, {0, 0});
    coordinator.addComponent<Destroy>(entity, 1000);
    Sender::sendEntity(coordinator, entity, EXPLOSION, type, {
        {POSITION, pos},
    });
}