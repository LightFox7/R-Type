/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** IMonster
*/

#pragma once

#include <any>

#include "Components.hpp"

class IMonster {
public:
    virtual ~IMonster() = default;
    virtual MonsterType getId() = 0;
    virtual bool isBoss() = 0;
    virtual std::map<ComponentType, std::any> create() = 0;
};
