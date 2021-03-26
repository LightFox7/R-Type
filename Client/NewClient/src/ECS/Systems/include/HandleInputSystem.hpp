/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** HandleInputSystem
*/

#pragma once

#include "ISystem.hpp"
#include "Core.hpp"
#include "Client.hpp"

class HandleInputSystem : public ISystem {
    public:
        HandleInputSystem();
        ~HandleInputSystem();
        void update(Core &core);
};
