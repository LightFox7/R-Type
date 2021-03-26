/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Game
*/

#pragma once

#include "Core.hpp"
#include "Coordinator.hpp"

// Systems
#include "DrawSystem.hpp"
#include "SpeedApplicationSystem.hpp"
#include "HandleInputSystem.hpp"
#include "NetworkHandlerSystem.hpp"
#include "AnimationSystem.hpp"

// Factories
#include "Player.hpp"
#include "IMonster.hpp"

#include "LoadMonsters.hpp"

class Game {
    public:
        Game(Core &core);
        ~Game();
        void loop();

    private:
        void initSystems();
        void updateSystems(float const &timePassed);

        Core &_core;
        Coordinator _coordinator;
        std::map<MonsterType, std::shared_ptr<IMonster>> _monsterCreators;
        std::list<void *> _monsterLibs;
};
