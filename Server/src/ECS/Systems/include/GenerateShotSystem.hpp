/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** GenerateShotSystem
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"
#include "PlayerShot.hpp"

class GenerateShotSystem : public ISystem{
public:
    GenerateShotSystem(Coordinator &coordinator);
    ~GenerateShotSystem();

private:
    void createShot(Coordinator &coordinator, Event &event);
    void createShotPlayer(Coordinator &coordinator, Entity const &entity);
};
