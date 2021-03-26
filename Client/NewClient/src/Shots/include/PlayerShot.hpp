/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** PlayerShot
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"

class PlayerShot {
    public:
        static Entity createLittle(Coordinator &coordinator, Entity const &id);
        static Entity createCharged(Coordinator &coordinator, Entity const &id);
};
