/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Player
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"

class Player {
    public:
        static Entity create(Coordinator &coordinator, PlayerId const &id = 0);
        static Entity create(Coordinator &coordinator, Entity const &entity, PlayerId const &id = 0);
};
