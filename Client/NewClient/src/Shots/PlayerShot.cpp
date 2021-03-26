/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** PlayerShot
*/

#include "PlayerShot.hpp"

static const std::map<int, AnimationFrame> animationLittleShotFrames =
{
    {0, AnimationFrame("r-typesheet1", 80, 202, 121, 30, 10, 15, 5)},
    {1, AnimationFrame("r-typesheet1", 80, 233, 120, 32, 12, 16, 6)},
};

static const std::map<int, Animation> animationsLittleShot =
{
    {0, Animation(animationLittleShotFrames, true)}
};

static const AnimationStore animationStoreLittleShot = AnimationStore(animationsLittleShot);

Entity PlayerShot::createLittle(Coordinator &coordinator, Entity const &id)
{
    Entity entity = coordinator.createEntity(id);

    coordinator.addComponent<EntityType>(entity, SHOT);
    coordinator.addComponent<Position>(entity, {0, 0});
    coordinator.addComponent<Speed>(entity, {700, 0});
    coordinator.addComponent<AnimationStore>(entity, animationStoreLittleShot);
    coordinator.addComponent<AnimationController>(entity, AnimationController());
    if (coordinator._core.ressources.isSoundLoaded("normal-shot"))
        coordinator._core.ressources.getSound("normal-shot")->play();
    return entity;
}

Entity PlayerShot::createCharged(Coordinator &coordinator, Entity const &id)
{
    Entity entity = coordinator.createEntity(id);

    coordinator.addComponent<EntityType>(entity, SHOT);
    coordinator.addComponent<Position>(entity, {0, 0});
    coordinator.addComponent<Speed>(entity, {600, 0});
    coordinator.addComponent<AnimationStore>(entity, animationStoreLittleShot);
    coordinator.addComponent<AnimationController>(entity, AnimationController());
    if (coordinator._core.ressources.isSoundLoaded("normal-shot"))
        coordinator._core.ressources.getSound("normal-shot")->play();
    return entity;
}