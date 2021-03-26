/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** ColisionSystem
*/

#pragma once

#include "Coordinator.hpp"
#include "Room.hpp"
#include "Components.hpp"

class HandleCollisionSystem : public ISystem {
    public:
        HandleCollisionSystem(Coordinator &coordinator);
        ~HandleCollisionSystem();
        void update(Coordinator &coordinator, Room &room);

    private:
        void collideTwoEntities(Coordinator &coordinator, Entity const &entity1, Entity const &entity2);
        bool checkCollision(Position const &pos1, HitBox &hitbox1, Position &pos2, HitBox &hitbox2);

        void handleCollision(Coordinator &coordinator, Event &event);

        void PlayerCollision(Coordinator &coordinator, Entity const &entity1, EntityType const &type1, Entity const &entity2, EntityType const &target);
        void ShotCollision(Coordinator &coordinator, Entity const &entity1, EntityType const &type1, Entity const &entity2, EntityType const &type2);
        void MonsterCollision(Coordinator &coordinator, Entity const &entity1, EntityType const &type1, Entity const &entity2, EntityType const &target);
        void WallCollision(Coordinator &coordinator, Entity const &entity1, EntityType const &type1, Entity const &entity2, EntityType const &target);
};
