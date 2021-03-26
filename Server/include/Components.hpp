/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Components
*/

#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>

#include "Types.hpp"

using PlayerId = std::uint16_t;
using MonsterType = std::uint32_t;
using Health = float;
using Destroy = double;

enum ComponentType
{
    ENTITYTYPE = 1,
    POSITION,
    SPEED,
    ACCELERATION,
    ANIMATIONCONTROLLER,
    ANIMATIONSTORE,
    HITBOX,
    SHOTCONTROLLER,
    SHOTTYPE,
    HEALTH,
    DESTROY,
    TIME,
    MONSTERBOSS,
    MYPATTERN,
    BOSS,
};

enum EntityType
{
    PLAYER = 0,
    STARFIELD,
    MONSTER,
    WALL,
    SHOT,
    EXPLOSION,
};

enum ExplosionType
{
    PLAYEREXPLOSION = 0,
    MONSTEREXPLOSION1
};

enum ShotType
{
    LITTLESHOT = 0,
    CHARGEDSHOT,
};

struct Position
{
    float x = 0;
    float y = 0;
};

struct Speed
{
    float x = 0;
    float y = 0;
};

struct Acceleration
{
    float x = 0;
    float y = 0;
};
struct Time {

    int time = 0;
    int initTime = 0;
};

struct AnimationFrame
{
    AnimationFrame(const std::string &assetId = "", float duration = 0, float left = 0, float top = 0, float width = 0, float height = 0, float offsetx = 0, float offsety = 0)
        : assetId(assetId), duration(duration), left(left), top(top), width(width), height(height), offsetx(offsetx), offsety(offsety) {}

    std::string const assetId = "";
    float duration = 0;
    int left = 0;
    int top = 0;
    int width = 0;
    int height = 0;
    float offsetx = 0;
    float offsety = 0;
};

struct Animation
{
    Animation() {}
    Animation(std::map<int, AnimationFrame> const &frames, bool const &isLooping = false) : _frames(frames), _isLooping(isLooping) {}
    AnimationFrame &getFrame(int id)
    {
        return (_frames.at(id));
    }
    bool hasFrame(int id)
    {
        return (_frames.find(id) != _frames.end());
    }

    std::map<int, AnimationFrame> _frames;
    bool _isLooping;
};

struct AnimationStore
{
    AnimationStore() {}
    AnimationStore(std::map<int, Animation> const &animations) : _animations(animations) {}
    Animation &getAnimation(int id)
    {
        return (_animations.at(id));
    }
    bool hasAnimation(int id)
    {
        return (_animations.find(id) != _animations.end());
    }

    std::map<int, Animation> _animations;
};

struct AnimationController {
    int actualAnimation = 0;
    int actualFrame = 0;
    float timeThisFrame = 0;
};

struct HitBox {
    float offsetx = 0;
    float offsety = 0;
    float width = 0;
    float height = 0;
};

struct ShotController {
    float damage = 0;
    bool pierce = false;
    std::set<Entity> hasHit;
};

struct DoExplode {
    bool doexplode = false;
};

struct MonsterBoss {
    bool isBoss = false;
};

struct PatternPart {
    Speed speed;
    float duration;
};

struct MyPattern {
    bool isLoopiong = true;
    float timeThisPart = 0;
    std::size_t actualIdx = 0;
    std::vector<PatternPart> pattern;
};