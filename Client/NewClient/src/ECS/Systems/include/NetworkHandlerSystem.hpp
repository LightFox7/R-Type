/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** NetworkHandlerSystem
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"
#include "Core.hpp"
#include "Player.hpp"
#include "IMonster.hpp"
#include "PlayerShot.hpp"
#include "Explosion.hpp"

class NetworkHandlerSystem : public ISystem{
    public:
        NetworkHandlerSystem();
        ~NetworkHandlerSystem();
        void update(Coordinator &coordinator, Core &core, std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators);

    private:
        void createEntity(Coordinator &coordinator, Response::ResponseStruct &response, std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators);
        void createMonster(Coordinator &coordinator, std::map<ComponentType, std::any> const &components, Entity const &id);
        void deleteEntity(Coordinator &coordinator, Response::ResponseStruct &response);
        void createComponent(Coordinator &coordinator, Response::ResponseStruct &response);
};
