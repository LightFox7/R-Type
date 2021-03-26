/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** DrawSystem
*/

#include "DrawSystem.hpp"

DrawSystem::DrawSystem()
{
}

DrawSystem::~DrawSystem()
{
}

void DrawSystem::update(Coordinator &coordinator, Core &core, float const &timePassed)
{
    std::set<Entity> entities = coordinator.getEntities();

    starfieldPos.x -= (timePassed / 1000) * 10;
    if (starfieldPos.x < -854)
        starfieldPos.x = 0;
    if (core.ressources.isTextureLoaded("starfield")) {
        starfield.setTexture(*core.ressources.getTexture("starfield"));
        starfield.setPosition({starfieldPos.x, starfieldPos.y});
        core.drawSprite(starfield);
    }
    for (auto entity : entities) {
        if (coordinator.hasComponent<AnimationStore>(entity) &&
        coordinator.hasComponent<AnimationController>(entity) && coordinator.hasComponent<Position>(entity)) {
            AnimationStore &animations = coordinator.getComponent<AnimationStore>(entity);
            AnimationController &controller = coordinator.getComponent<AnimationController>(entity);
            Position &pos = coordinator.getComponent<Position>(entity);
            if (animations.hasAnimation(controller.actualAnimation))
                drawFrame(core, animations, controller, pos);
        }
    }
}

void DrawSystem::drawFrame(Core &core, AnimationStore &animations, AnimationController &controller, Position &pos)
{
    Animation &animation = animations.getAnimation(controller.actualAnimation);
    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture = nullptr;

    if (!animation.hasFrame(controller.actualFrame))
        return;
    AnimationFrame &frame = animation.getFrame(controller.actualFrame);
    texture = core.ressources.getTexture(frame.assetId);
    if (!texture)
        return;
    sprite.setTexture(*texture);
    sprite.setTextureRect({frame.left, frame.top, frame.width, frame.height});
    sprite.setOrigin({frame.offsetx, frame.offsety});
    sprite.setPosition({pos.x, pos.y});
    core.drawSprite(sprite);
}