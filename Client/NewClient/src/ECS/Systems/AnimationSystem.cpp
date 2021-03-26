/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** AnimationSystem
*/

#include "AnimationSystem.hpp"

AnimationSystem::AnimationSystem()
{
}

AnimationSystem::~AnimationSystem()
{
}

void AnimationSystem::update(Coordinator &coordinator, float const &timePassed)
{
    std::set<Entity> entities = coordinator.getEntities();
    EntityType type;

    for (auto entity : entities) {
        updateAnimation(coordinator, entity, timePassed);
        if (coordinator.hasComponent<EntityType>(entity)) {
            type = coordinator.getComponent<EntityType>(entity);
            if (type == PLAYER)
                updatePlayer(coordinator, entity);
        }
    }
}

void AnimationSystem::updateAnimation(Coordinator &coordinator, Entity const &entity, float const &timePassed)
{
    if (coordinator.hasComponent<AnimationController>(entity) && coordinator.hasComponent<AnimationStore>(entity)) {
        AnimationController &controller = coordinator.getComponent<AnimationController>(entity);
        AnimationStore &store = coordinator.getComponent<AnimationStore>(entity);
        controller.timeThisFrame += timePassed;
        if (store.hasAnimation(controller.actualAnimation) && store.getAnimation(controller.actualAnimation).hasFrame(controller.actualFrame)) {
            AnimationFrame actualframe = store.getAnimation(controller.actualAnimation).getFrame(controller.actualFrame);
            if (controller.timeThisFrame > actualframe.duration) {
                controller.timeThisFrame = 0;
                if (store.getAnimation(controller.actualAnimation).hasFrame(controller.actualFrame + 1))
                    controller.actualFrame += 1;
                else if (store.getAnimation(controller.actualAnimation)._isLooping && store.getAnimation(controller.actualAnimation).hasFrame(0))
                    controller.actualFrame = 0;
            }
        }
    }
}

void AnimationSystem::updatePlayer(Coordinator &coordinator, Entity const &entity)
{
    if (!coordinator.hasComponent<Speed>(entity))
        return;
    Speed &speed = coordinator.getComponent<Speed>(entity);
    AnimationController &controller = coordinator.getComponent<AnimationController>(entity);
    int animation = controller.actualAnimation;

    if (speed.y > 1)
        controller.actualAnimation = 1;
    else if (speed.y < -1)
        controller.actualAnimation = 2;
    else
        controller.actualAnimation = 0;
    if (controller.actualAnimation != animation) {
        controller.actualFrame = 0;
        controller.timeThisFrame = 0;
    }
}