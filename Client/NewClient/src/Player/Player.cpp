/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Player
*/

#include "Player.hpp"

static const std::map<int, AnimationFrame> idleAnimationBlueFrames =
{
    {0, AnimationFrame("r-typesheet42", 150, 67, 2, 32, 15, 16, 7)}
};
static const std::map<int, AnimationFrame> downAnimationBlueFrames =
{
    {0, AnimationFrame("r-typesheet42", 150, 34, 2, 32, 15, 16, 7)},
    {1, AnimationFrame("r-typesheet42", 150, 1, 2, 32, 15, 16, 7)},
};
static const std::map<int, AnimationFrame> upAnimationBlueFrames =
{
    {0, AnimationFrame("r-typesheet42", 150, 100, 2, 32, 15, 16, 7)},
    {1, AnimationFrame("r-typesheet42", 150, 133, 2, 32, 15, 16, 7)}
};
static const std::map<int, Animation> animationsBlue =
{
    {0, Animation(idleAnimationBlueFrames)},
    {1, Animation(downAnimationBlueFrames)},
    {2, Animation(upAnimationBlueFrames)},
};
static const AnimationStore animationStoreBlue = AnimationStore(animationsBlue);

static const std::map<int, AnimationFrame> idleAnimationPurpleFrames =
{
    {0, AnimationFrame("r-typesheet42", 150, 67, 19, 32, 15, 16, 7)}
};
static const std::map<int, AnimationFrame> downAnimationPurpleFrames =
{
    {0, AnimationFrame("r-typesheet42", 150, 34, 19, 32, 15, 16, 7)},
    {1, AnimationFrame("r-typesheet42", 150, 1, 19, 32, 15, 16, 7)},
};
static const std::map<int, AnimationFrame> upAnimationPurpleFrames =
{
    {0, AnimationFrame("r-typesheet42", 150, 100, 19, 32, 15, 16, 7)},
    {1, AnimationFrame("r-typesheet42", 150, 133, 19, 32, 15, 16, 7)}
};
static const std::map<int, Animation> animationsPurple =
{
    {0, Animation(idleAnimationPurpleFrames)},
    {1, Animation(downAnimationPurpleFrames)},
    {2, Animation(upAnimationPurpleFrames)},
};
static const AnimationStore animationStorePurple = AnimationStore(animationsPurple);

static const std::map<int, AnimationFrame> idleAnimationGreenFrames =
{
    {0, AnimationFrame("r-typesheet42", 150, 67, 36, 32, 15, 16, 7)}
};
static const std::map<int, AnimationFrame> downAnimationGreenFrames =
{
    {0, AnimationFrame("r-typesheet42", 150, 34, 36, 32, 15, 16, 7)},
    {1, AnimationFrame("r-typesheet42", 150, 1, 36, 32, 15, 16, 7)},
};
static const std::map<int, AnimationFrame> upAnimationGreenFrames =
{
    {0, AnimationFrame("r-typesheet42", 150, 100, 36, 32, 15, 16, 7)},
    {1, AnimationFrame("r-typesheet42", 150, 133, 36, 32, 15, 16, 7)}
};
static const std::map<int, Animation> animationsGreen =
{
    {0, Animation(idleAnimationGreenFrames)},
    {1, Animation(downAnimationGreenFrames)},
    {2, Animation(upAnimationGreenFrames)},
};
static const AnimationStore animationStoreGreen = AnimationStore(animationsGreen);

static const std::map<int, AnimationFrame> idleAnimationRedFrames =
{
    {0, AnimationFrame("r-typesheet42", 150, 67, 53, 32, 15, 16, 7)}
};
static const std::map<int, AnimationFrame> downAnimationRedFrames =
{
    {0, AnimationFrame("r-typesheet42", 150, 34, 53, 32, 15, 16, 7)},
    {1, AnimationFrame("r-typesheet42", 150, 1, 53, 32, 15, 16, 7)},
};
static const std::map<int, AnimationFrame> upAnimationRedFrames =
{
    {0, AnimationFrame("r-typesheet42", 150, 100, 53, 32, 15, 16, 7)},
    {1, AnimationFrame("r-typesheet42", 150, 133, 53, 32, 15, 16, 7)}
};
static const std::map<int, Animation> animationsRed =
{
    {0, Animation(idleAnimationRedFrames)},
    {1, Animation(downAnimationRedFrames)},
    {2, Animation(upAnimationRedFrames)},
};
static const AnimationStore animationStoreRed = AnimationStore(animationsRed);

static const std::map<int, AnimationStore> playerAnimationStores =
{
    {1, animationStoreBlue},
    {2, animationStorePurple},
    {3, animationStoreGreen},
    {4, animationStoreRed},
};

Entity Player::create(Coordinator &coordinator, PlayerId const &id)
{
    Entity player = coordinator.createEntity();

    coordinator.addComponent<EntityType>(player, PLAYER);
    coordinator.addComponent<PlayerId>(player, id);
    coordinator.addComponent<Position>(player, {0, 0});
    coordinator.addComponent<Speed>(player, {0, 0});
    if (id > 4 || id < 1)
        coordinator.addComponent<AnimationStore>(player, animationStoreBlue);
    else
        coordinator.addComponent<AnimationStore>(player, playerAnimationStores.find(id)->second);
    coordinator.addComponent<AnimationController>(player, AnimationController());
    return player;
}

Entity Player::create(Coordinator &coordinator, Entity const &entity, PlayerId const &id)
{
    Entity player = coordinator.createEntity(entity);

    coordinator.addComponent<EntityType>(player, PLAYER);
    coordinator.addComponent<PlayerId>(player, id);
    coordinator.addComponent<Position>(player, {0, 0});
    coordinator.addComponent<Speed>(player, {0, 0});
    if (id > 4 || id < 1)
        coordinator.addComponent<AnimationStore>(player, animationStoreBlue);
    else
        coordinator.addComponent<AnimationStore>(player, playerAnimationStores.find(id)->second);
    coordinator.addComponent<AnimationController>(player, AnimationController());
    return player;
}