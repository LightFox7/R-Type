/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** HandleInputSystem
*/

#pragma once

#include "Coordinator.hpp"
#include "Room.hpp"
#include "Components.hpp"

class HandleInputSystem : public ISystem {
    public:
        HandleInputSystem();
        ~HandleInputSystem();
        void update(Coordinator &coordinator, Room &room);

    private:
        void applyToPlayer(Coordinator &Coordinator, Room &room, Entity const &entity);
};
