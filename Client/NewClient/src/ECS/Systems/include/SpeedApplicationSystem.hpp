/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** SpeedApplicationSystem
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"

class SpeedApplicationSystem : public ISystem {
    public:
        SpeedApplicationSystem();
        ~SpeedApplicationSystem();
        void update(Coordinator &Coordinator, float const &timePassed);
};
