/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** ComponentManager
*/

#include "ComponentManager.hpp"

ComponentManager::ComponentManager()
{
}

ComponentManager::~ComponentManager()
{
}

void ComponentManager::entityDestroyed(Entity entity)
{
    for (auto it : _componentArrays) {
        it.second->deleteComponent(entity);
    }
}