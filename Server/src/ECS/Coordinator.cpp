/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Coordinator
*/

#include "Coordinator.hpp"

Coordinator::Coordinator(Room &room) : _room(room)
{
    _entityManager = std::make_unique<EntityManager>();
    _componentManager = std::make_unique<ComponentManager>();
    _systemManager = std::make_unique<SystemManager>();
    _eventManager = std::make_unique<EventManager>();
}

Coordinator::~Coordinator()
{
}

Entity Coordinator::createEntity(void)
{
    return _entityManager->createEntity();
}

void Coordinator::removeEntity(Room &room, Entity const &id)
{
    _entityManager->removeEntity(id);
    _componentManager->entityDestroyed(id);
    Sender::sendDestroyEntity(*this, id);
}

std::set<Entity> Coordinator::getEntities(void)
{
    return _entityManager->getEntities();
}

void Coordinator::AddEventListener(EventId eventId, std::function<void(Coordinator&, Event&)> const& listener)
{
    _eventManager->AddListener(eventId, listener);
}

void Coordinator::SendEvent(Coordinator &coordinator, Event& event)
{
    _eventManager->SendEvent(coordinator, event);
}

void Coordinator::SendEvent(Coordinator &coordinator, EventId event)
{
    _eventManager->SendEvent(coordinator, event);
}

void Coordinator::addComponent(Entity entity, ComponentType type, std::any component)
{
    if (type == ENTITYTYPE)
        return _componentManager->addComponent<EntityType>(entity, std::any_cast<EntityType>(component));
    else if (type == POSITION)
        return _componentManager->addComponent<Position>(entity, std::any_cast<Position>(component));
    else if (type == SPEED)
        return _componentManager->addComponent<Speed>(entity, std::any_cast<Speed>(component));
    else if (type == ACCELERATION)
        return _componentManager->addComponent<Acceleration>(entity, std::any_cast<Acceleration>(component));
    else if (type == ANIMATIONCONTROLLER)
        return _componentManager->addComponent<AnimationController>(entity, std::any_cast<AnimationController>(component));
    else if (type == ANIMATIONSTORE)
        return _componentManager->addComponent<AnimationStore>(entity, std::any_cast<AnimationStore>(component));
    else if (type == HITBOX)
        return _componentManager->addComponent<HitBox>(entity, std::any_cast<HitBox>(component));
    else if (type == SHOTCONTROLLER)
        return _componentManager->addComponent<ShotController>(entity, std::any_cast<ShotController>(component));
    else if (type == HEALTH)
        return _componentManager->addComponent<Health>(entity, std::any_cast<Health>(component));
    else if (type == DESTROY)
        return _componentManager->addComponent<Destroy>(entity, std::any_cast<Destroy>(component));
    else if (type == TIME)
        return _componentManager->addComponent<Time>(entity, std::any_cast<Time>(component));
    else if (type == MONSTERBOSS)
        return _componentManager->addComponent<MonsterBoss>(entity, std::any_cast<MonsterBoss>(component));
    else if (type == MYPATTERN)
        return _componentManager->addComponent<MyPattern>(entity, std::any_cast<MyPattern>(component));
    else if (type == BOSS)
        return _componentManager->addComponent<MonsterBoss>(entity, std::any_cast<MonsterBoss>(component));
    return;
}