/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Monster3
*/

#include "Monster3.hpp"

static const std::map<int, AnimationFrame> idleAnimationMonster3Frames =
{
    {0, AnimationFrame("r-typesheet28", 80, 0, 0, 150, 50, 75, 25)},

};
static const std::map<int, Animation> animationsMonster3 =
{
    {0, Animation(idleAnimationMonster3Frames, true)}
};
static const AnimationStore animationStoreMonster3 = AnimationStore(animationsMonster3);

static const MyPattern monster3Pattern = {
    false, 0, 0, {
        {{-100, 0}, 2000},
        {{0, 20}, 10000},
        {{0, -20}, 10000},
        {{-1000, 0}, 5000},
    },
};

Monster3::Monster3()
{
}

Monster3::~Monster3()
{
}

MonsterType Monster3::getId()
{
    return (3);
}

bool Monster3::isBoss()
{
    return true;
}

std::map<ComponentType, std::any> Monster3::create()
{
    std::map<ComponentType, std::any> componentMap;

    std::vector<std::pair<Speed, Time>> moovevalue;

    componentMap.emplace(ENTITYTYPE, MONSTER);
    componentMap.emplace(POSITION, Position({0, 0}));
    componentMap.emplace(SPEED, Speed({-200, 0}));
    componentMap.emplace(ANIMATIONSTORE, animationStoreMonster3);
    componentMap.emplace(ANIMATIONCONTROLLER, AnimationController());
    componentMap.emplace(HITBOX, HitBox{-75, -25, 150, 50});
    componentMap.emplace(HEALTH, (Health)(300.0));
    componentMap.emplace(MYPATTERN, monster3Pattern);
    componentMap.emplace(BOSS, MonsterBoss{true});

    return (componentMap);
}