/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** ComponentArray
*/

#pragma once

#include <unordered_map>

#include "Types.hpp"
#include "IComponentArray.hpp"

template<typename T>
class ComponentArray : public IComponentArray {
    public:
        void addComponent(Entity entity, T component);
        void deleteComponent(Entity entity);
        bool hasComponent(Entity entity);
        T& getComponent(Entity entity);

    private:
        std::unordered_map<Entity, T> _components;
};

template<typename T>
void ComponentArray<T>::addComponent(Entity entity, T component)
{
    if (_components.find(entity) != _components.end())
        _components.at(entity) = component;
    else
        _components.insert(std::pair<Entity, T>(entity, component));
}

template<typename T>
void ComponentArray<T>::deleteComponent(Entity entity)
{
    if (_components.find(entity) == _components.end())
        return;
    _components.erase(entity);
}

template<typename T>
bool ComponentArray<T>::hasComponent(Entity entity)
{
    if (_components.find(entity) == _components.end())
        return false;
    return true;
}

template<typename T>
T& ComponentArray<T>::getComponent(Entity entity)
{
    return _components.at(entity);
}