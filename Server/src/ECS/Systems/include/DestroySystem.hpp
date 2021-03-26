/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** DestroySystem
*/

#pragma once

#include "Coordinator.hpp"
#include "Room.hpp"
#include "Components.hpp"
#include "Explosion.hpp"

class DestroySystem : public ISystem{
    public:
        DestroySystem();
        ~DestroySystem();
        void update(Coordinator &coordinator, Room &room, float const &timePassed);

    private:
        void destroyEntity(Coordinator &coordinator, Entity const &entity);
        void checkDestroyShot(Coordinator &coordinator, Entity const &entity);
        void checkDestroyMonster(Coordinator &coordinator, Entity const &entity);
};
