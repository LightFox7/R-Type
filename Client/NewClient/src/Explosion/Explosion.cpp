/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Explosion
*/

#include "Explosion.hpp"

static const std::map<int, AnimationFrame> animationMonster1ExplosionFrames =
{
    {0, AnimationFrame("r-typesheet44", 50, 130, 1, 26, 25, 13, 12)},
    {1, AnimationFrame("r-typesheet44", 50, 162, 1, 31, 32, 16, 16)},
    {2, AnimationFrame("r-typesheet44", 50, 194, 1, 32, 32, 16, 16)},
    {3, AnimationFrame("r-typesheet44", 50, 228, 2, 31, 30, 15, 15)},
    {4, AnimationFrame("r-typesheet44", 50, 261, 4, 31, 27, 15, 13)},
    {4, AnimationFrame("r-typesheet44", 50, 294, 1, 31, 31, 15, 15)},
    {5, AnimationFrame("r-typesheet44")},
};
static const std::map<int, Animation> animationsMonster1Explosion =
{
    {0, Animation(animationMonster1ExplosionFrames)},
};
static const AnimationStore animationStoreMonster1Explosion = AnimationStore(animationsMonster1Explosion);

static const std::map<int, AnimationFrame> animationPlayerExplosionFrames =
{
    {0, AnimationFrame("r-typesheet1", 40, 57, 204, 24, 22, 12, 11)},
    {1, AnimationFrame("r-typesheet1", 40, 83, 201, 32, 28, 16, 7)},
    {2, AnimationFrame("r-typesheet1", 40, 117, 198, 40, 34, 20, 17)},
    {3, AnimationFrame("r-typesheet1", 40, 159, 194, 48, 42, 24, 22)},
    {4, AnimationFrame("r-typesheet1", 40, 209, 191, 56, 48, 28, 24)},
    {5, AnimationFrame("r-typesheet1")},
};
static const std::map<int, Animation> animationsPlayerExplosion =
{
    {0, Animation(animationPlayerExplosionFrames)},
};
static const AnimationStore animationStorePlayerExplosion = AnimationStore(animationsPlayerExplosion);


Entity Explosion::createExplosion(Coordinator &coordinator, Entity const &id, ExplosionType const &type)
{
    Entity entity = coordinator.createEntity(id);

    coordinator.addComponent<EntityType>(entity, EXPLOSION);
    coordinator.addComponent<ExplosionType>(entity, type);
    coordinator.addComponent<Position>(entity, {0, 0});
    coordinator.addComponent<Speed>(entity, {0, 0});
    coordinator.addComponent<AnimationController>(entity, AnimationController());
    if (type == PLAYEREXPLOSION)
        coordinator.addComponent<AnimationStore>(entity, animationStorePlayerExplosion);
    else if (type == MONSTEREXPLOSION1) {
        coordinator.addComponent<AnimationStore>(entity, animationStoreMonster1Explosion);
        if (coordinator._core.ressources.isSoundLoaded("explosion1"))
            coordinator._core.ressources.getSound("explosion1")->play();
    }
    return entity;
}