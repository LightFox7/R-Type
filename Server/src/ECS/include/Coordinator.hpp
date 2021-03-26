/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Coordinator
*/

#pragma once

#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "EventManager.hpp"
#include "ComponentManager.hpp"
#include "Components.hpp"

class Room;

class Coordinator {
    public:
        Coordinator(Room &room);
        ~Coordinator();
        Entity createEntity(void);
        void removeEntity(Room &room, Entity const &id);
        std::set<Entity> getEntities(void);
        template<typename T>
        void addComponent(Entity entity, T component);
        void addComponent(Entity entity, ComponentType type, std::any component);
        template<typename T>
        void removeComponent(Entity entity);
        template<typename T>
        bool hasComponent(Entity entity);
        template<typename T>
        T& getComponent(Entity entity);
        template<typename T>
        void AddSystem(T system);
        template<typename T>
        void RemoveSystem();
        template<typename T>
        std::shared_ptr<T> getSystem(void) const;
        void AddEventListener(EventId eventId, std::function<void(Coordinator&, Event&)> const& listener);
        void SendEvent(Coordinator &coordinator, Event& event);
        void SendEvent(Coordinator &coordinator, EventId eventId);
        Room &_room;

    private:
        std::unique_ptr<EntityManager> _entityManager;
        std::unique_ptr<ComponentManager> _componentManager;
        std::unique_ptr<SystemManager> _systemManager;
        std::unique_ptr<EventManager> _eventManager;
};

template<typename T>
void Coordinator::addComponent(Entity entity, T component)
{
    return _componentManager->addComponent<T>(entity, component);
}

template<typename T>
void Coordinator::removeComponent(Entity entity)
{
    return _componentManager->removeComponent<T>(entity);
}

template<typename T>
bool Coordinator::hasComponent(Entity entity)
{
    return _componentManager->hasComponent<T>(entity);
}

template<typename T>
T& Coordinator::getComponent(Entity entity)
{
    return _componentManager->getComponent<T>(entity);
}

template<typename T>
void Coordinator::AddSystem(T system)
{
    return _systemManager->AddSystem<T>(system);
}

template<typename T>
void Coordinator::RemoveSystem()
{
    return _systemManager->RemoveSystem<T>();
}

template<typename T>
std::shared_ptr<T> Coordinator::getSystem() const
{
    return _systemManager->getSystem<T>();
}

#include "Room.hpp"
#include "Sender.hpp"