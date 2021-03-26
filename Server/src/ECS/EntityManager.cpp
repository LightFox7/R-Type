/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** EntityManager
*/

#include "EntityManager.hpp"

EntityManager::EntityManager()
{
    for (Entity i = 0; i < MAX_ENTITIES; i++)
        _available_ids.push_back(i);
}

EntityManager::~EntityManager()
{
}

Entity EntityManager::createEntity(void)
{
    Entity id = _available_ids.front();

    _used_ids.insert(id);
    _available_ids.pop_front();
    return id;
}

void EntityManager::removeEntity(Entity const &id)
{
    if (_used_ids.find(id) != _used_ids.end()) {
        _used_ids.erase(id);
        _available_ids.push_front(id);
    }
}

std::set<Entity> EntityManager::getEntities(void)
{
    return _used_ids;
}