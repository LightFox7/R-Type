/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** DrawSystem
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"
#include "Core.hpp"

class DrawSystem : public ISystem {
    public:
        DrawSystem();
        ~DrawSystem();
        void update(Coordinator &Coordinator, Core &core, float const &timePassed);

    private:
        void drawFrame(Core &core, AnimationStore &store, AnimationController &controller, Position &pos);
        sf::Sprite starfield;
        Position starfieldPos;
};
