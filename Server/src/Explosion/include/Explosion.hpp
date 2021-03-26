/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Explosion
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"

class Explosion {
    public:
        static void createExplosion(Coordinator &coordinator, ExplosionType const &type = MONSTEREXPLOSION1, Position pos = {0, 0});
};