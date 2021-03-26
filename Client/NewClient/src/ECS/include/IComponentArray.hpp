/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** IComponentArray
*/

#pragma once

#include "EntityManager.hpp"

class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void deleteComponent(Entity entity) = 0;
};
