/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** SystemManager
*/

#include "SystemManager.hpp"

std::unordered_map<const char*, std::shared_ptr<ISystem>> SystemManager::getSystems(void) const
{
    return _systems;
}