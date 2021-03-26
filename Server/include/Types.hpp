/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Types
*/

#pragma once

#include <iostream>

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 512;

using EventId = std::uint32_t;
using ParamId = std::uint32_t;

#define METHOD_LISTENER(EventType, Listener) EventType, std::bind(&Listener, this, std::placeholders::_1, std::placeholders::_2)
#define FUNCTION_LISTENER(EventType, Listener) EventType, std::bind(&Listener, std::placeholders::_1, std::placeholders::_2)

namespace Events {
    const EventId GENERATESHOT = 2;
    namespace GenerateShot {
        const ParamId SHOOTER = 0;
    };
    const EventId COLLIDE = 3;
    namespace Collide {
        const ParamId ENTITY1 = 0;
        const ParamId ENTITY2 = 1;
    }
};