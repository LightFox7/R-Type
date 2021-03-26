/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** HandleMonsterSpeed
*/

#pragma once

#include "Coordinator.hpp"
#include "Room.hpp"
#include "Components.hpp"

class HandleMonsterSpeed : public ISystem {
    public:
        HandleMonsterSpeed(Coordinator &coordinator);
        ~HandleMonsterSpeed();
        void update(Coordinator &coordinator, float const &timePassed);

    private:
};