/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** HandleRequestsSystem
*/

#pragma once

#include "ISystem.hpp"
#include "Room.hpp"
#include "Coordinator.hpp"
#include "Components.hpp"

class HandleRequestsSystem : public ISystem {
public:
    HandleRequestsSystem();
    ~HandleRequestsSystem();
    void update(Room &room, Coordinator &coordinator);
};
