/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Coordinator
*/

#include "Coordinator.hpp"

Coordinator::Coordinator(Core &core) : _core(core)
{
    _entityManager = std::make_unique<EntityManager>();
    _componentManager = std::make_unique<ComponentManager>();
    _systemManager = std::make_unique<SystemManager>();
}

Coordinator::~Coordinator()
{
}

Entity Coordinator::createEntity(void)
{
    return _entityManager->createEntity();
}

Entity Coordinator::createEntity(Entity const &entity)
{
    _entityManager->removeEntity(entity);
    _componentManager->entityDestroyed(entity);
    return _entityManager->createEntity(entity);
}

void Coordinator::removeEntity(Entity const &id)
{
    _entityManager->removeEntity(id);
    _componentManager->entityDestroyed(id);
}

std::set<Entity> Coordinator::getEntities(void)
{
    return _entityManager->getEntities();
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
    return;
}