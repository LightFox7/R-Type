/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Monster2
*/

#include "Monster2.hpp"

static const std::map<int, AnimationFrame> idleAnimationMonster2Frames =
{
    {0, AnimationFrame("r-typesheet21", 80, 34, 364, 32, 28, 16, 14)},
    {1, AnimationFrame("r-typesheet21", 80, 69, 363, 31, 29, 15, 14)},
    {2, AnimationFrame("r-typesheet21", 80, 102, 364, 32, 31, 16, 15)},
    {3, AnimationFrame("r-typesheet21", 80, 136, 365, 31, 28, 15, 14)},
    {4, AnimationFrame("r-typesheet21", 80, 169, 365, 32, 30, 16, 15)},
    {5, AnimationFrame("r-typesheet21", 80, 203, 364, 32, 31, 16, 15)},
    {6, AnimationFrame("r-typesheet21", 80, 237, 365, 32, 27, 16, 13)},
    {7, AnimationFrame("r-typesheet21", 80, 271, 366, 32, 27, 16, 13)},
    {8, AnimationFrame("r-typesheet21", 80, 305, 366, 32, 28, 16, 14)},
    {9, AnimationFrame("r-typesheet21", 80, 339, 366, 32, 29, 16, 14)},
    {10, AnimationFrame("r-typesheet21", 80, 373, 363, 32, 31, 16, 15)},
    {11, AnimationFrame("r-typesheet21", 80, 408, 365, 31, 28, 16, 14)},
    {12, AnimationFrame("r-typesheet21", 80, 441, 363, 32, 30, 16, 15)},
    {13, AnimationFrame("r-typesheet21", 80, 475, 363, 32, 31, 16, 15)},
    {14, AnimationFrame("r-typesheet21", 80, 509, 366, 32, 27, 16, 13)},
    {15, AnimationFrame("r-typesheet21", 80, 543, 365, 32, 27, 16, 13)},
};

static const std::map<int, Animation> animationsMonster2 =
{
    {0, Animation(idleAnimationMonster2Frames, true)}
};

static const AnimationStore animationStoreMonster2 = AnimationStore(animationsMonster2);

static const MyPattern monster2Pattern = {
    true, 0, 0, {
        {{-300, 0}, 400},
        {{-300, -200}, 200},
        {{0, -200}, 200},
        {{200, -200}, 200},
        {{200, 0}, 200},
        {{200, 200}, 200},
        {{0, 200}, 200},
        {{-300, 200}, 200},
    },
};

Monster2::Monster2()
{
}

Monster2::~Monster2()
{
}

MonsterType Monster2::getId()
{
    return (2);
}

bool Monster2::isBoss()
{
    return false;
}

std::map<ComponentType, std::any> Monster2::create()
{
    std::map<ComponentType, std::any> componentMap;

    componentMap.emplace(ENTITYTYPE, MONSTER);
    componentMap.emplace(POSITION, Position({0, 0}));
    componentMap.emplace(SPEED, Speed({-200, 0}));
    componentMap.emplace(ANIMATIONSTORE, animationStoreMonster2);
    componentMap.emplace(ANIMATIONCONTROLLER, AnimationController());
    componentMap.emplace(HITBOX, HitBox{-11, -12, 21, 24});
    componentMap.emplace(HEALTH, (Health)(20.0));
    componentMap.emplace(MYPATTERN, monster2Pattern);
    return (componentMap);
}