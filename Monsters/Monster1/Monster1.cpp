/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Monster1
*/

#include "Monster1.hpp"

#include <iostream>
#include <utility>
#include <functional>

static const std::map<int, AnimationFrame> idleAnimationMonster1Frames =
{
    {0, AnimationFrame("r-typesheet5", 80, 5, 6, 21, 24, 11, 12)},
    {1, AnimationFrame("r-typesheet5", 80, 38, 6, 21, 24, 11, 12)},
    {2, AnimationFrame("r-typesheet5", 80, 71, 6, 21, 24, 11, 12)},
    {3, AnimationFrame("r-typesheet5", 80, 104, 6, 21, 24, 11, 12)},
    {4, AnimationFrame("r-typesheet5", 80, 137, 6, 21, 24, 11, 12)},
    {5, AnimationFrame("r-typesheet5", 80, 170, 6, 21, 24, 11, 12)},
    {6, AnimationFrame("r-typesheet5", 80, 203, 6, 21, 24, 11, 12)},
    {7, AnimationFrame("r-typesheet5", 80, 236, 6, 21, 24, 11, 12)},
};

static const std::map<int, Animation> animationsMonster1 =
{
    {0, Animation(idleAnimationMonster1Frames, true)}
};

static const AnimationStore animationStoreMonster1 = AnimationStore(animationsMonster1);

static const MyPattern monster1Pattern = {
    true, 0, 0, {
        {{-150, -60}, 1500},
        {{-150, 60}, 1500},
    },
};

Monster1::Monster1()
{
}

Monster1::~Monster1()
{
}

MonsterType Monster1::getId()
{
    return (1);
}

bool Monster1::isBoss()
{
    return false;
}

std::map<ComponentType, std::any> Monster1::create()
{
    std::map<ComponentType, std::any> componentMap;

    componentMap.emplace(ENTITYTYPE, MONSTER);
    componentMap.emplace(POSITION, Position({0, 0}));
    componentMap.emplace(SPEED, Speed({0, 0}));
    componentMap.emplace(ANIMATIONSTORE, animationStoreMonster1);
    componentMap.emplace(ANIMATIONCONTROLLER, AnimationController());
    componentMap.emplace(HITBOX, HitBox{-11, -12, 21, 24});
    componentMap.emplace(HEALTH, (Health)(10.0));
    componentMap.emplace(TIME, Time{100, 100});
    componentMap.emplace(MYPATTERN, monster1Pattern);

    return (componentMap);
}