/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** ComponentManager
*/

#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>

#include "Types.hpp"
#include "ComponentArray.hpp"

class ComponentManager {
    public:
        ComponentManager();
        ~ComponentManager();
        template<typename T>
        void addComponent(Entity entity, T component);
        template<typename T>
        void removeComponent(Entity entity);
        void entityDestroyed(Entity entity);
        template<typename T>
        bool hasComponent(Entity entity);
        template<typename T>
        T& getComponent(Entity entity);

    private:
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> _componentArrays;

        template<typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray(void);
};

template<typename T>
void ComponentManager::addComponent(Entity entity, T component)
{
    if (getComponentArray<T>() == nullptr)
        _componentArrays.insert(std::pair<const char*, std::shared_ptr<IComponentArray>>(typeid(T).name(), std::make_shared<ComponentArray<T>>()));
    return getComponentArray<T>()->addComponent(entity, component);
}

template<typename T>
void ComponentManager::removeComponent(Entity entity)
{
    if (getComponentArray<T>() == nullptr)
        return;
    return getComponentArray<T>()->removeComponent(entity);
}

template<typename T>
bool ComponentManager::hasComponent(Entity entity)
{
    if (getComponentArray<T>() == nullptr)
        return false;
    return getComponentArray<T>()->hasComponent(entity);
}

template<typename T>
T& ComponentManager::getComponent(Entity entity)
{
    return getComponentArray<T>()->getComponent(entity);
}

template<typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::getComponentArray(void)
{
    const char* typeName = typeid(T).name();

    if (_componentArrays.find(typeName) == _componentArrays.end())
        return nullptr;
    return std::static_pointer_cast<ComponentArray<T>>(_componentArrays.at(typeName));
}