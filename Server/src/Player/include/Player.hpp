/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Player
*/

#pragma once

#include "Room.hpp"
#include "Coordinator.hpp"
#include "Components.hpp"

class Player {
    public:
        static Entity create(Coordinator &coordinator, PlayerId id = 0, Position pos = {0, 0});
};
