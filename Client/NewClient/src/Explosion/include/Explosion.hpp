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
        static Entity createExplosion(Coordinator &coordinator, Entity const &entity, ExplosionType const &type = MONSTEREXPLOSION1);
};