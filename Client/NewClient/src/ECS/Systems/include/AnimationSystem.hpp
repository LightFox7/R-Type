/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** AnimationSystem
*/

#pragma once

#include "Coordinator.hpp"

class AnimationSystem : public ISystem{
    public:
        AnimationSystem();
        ~AnimationSystem();
        void update(Coordinator &coordinator, float const &timePassed);

    private:
        void updateAnimation(Coordinator &coordinator, Entity const &entity, float const &timepassed);
        void updatePlayer(Coordinator &coordinator, Entity const &entity);
};
