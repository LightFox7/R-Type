/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** SystemManager
*/

#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>

#include "ISystem.hpp"

class SystemManager {
    public:
        SystemManager() = default;
        ~SystemManager() = default;
        template<typename T>
        void AddSystem(T system);
        template<typename T>
        void RemoveSystem();
        template<typename T>
        std::shared_ptr<T> getSystem() const;
        std::unordered_map<const char*, std::shared_ptr<ISystem>> getSystems(void) const;

    private:
        std::unordered_map<const char*, std::shared_ptr<ISystem>> _systems;
};

template<typename T>
void SystemManager::AddSystem(T system)
{
    const char* typeName = typeid(T).name();
    if (_systems.find(typeName) != _systems.end()) {
        std::cerr << "System " << typeName << " already exists" << std::endl;
        return;
    }
    _systems.emplace(typeName, std::make_shared<T>(system));
}

template<typename T>
void SystemManager::RemoveSystem()
{
    const char* typeName = typeid(T).name();
    if (_systems.find(typeName) == _systems.end()) {
        std::cerr << "Can't find System " << typeName << std::endl;
        return;
    }
    _systems.erase(typeName);
}

template<typename T>
std::shared_ptr<T> SystemManager::getSystem() const
{
    const char* typeName = typeid(T).name();
    if (_systems.find(typeName) == _systems.end()) {
        std::cerr << "Can't find System " << typeName << std::endl;
        return nullptr;
    }
    return std::static_pointer_cast<T>(_systems.at(typeName));
}