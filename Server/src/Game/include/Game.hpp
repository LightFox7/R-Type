/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Game
*/

#pragma once

#include "Exception.hpp"
#include "Room.hpp"
#include "Coordinator.hpp"

// Systems
#include "SpeedApplicationSystem.hpp"
#include "HandleInputSystem.hpp"
#include "GenerateShotSystem.hpp"
#include "HandleRequestsSystem.hpp"
#include "HandleCollisionSystem.hpp"
#include "DestroySystem.hpp"
#include "HandleMonsterSpeed.hpp"
#include "GenerateMonstersSystem.hpp"

// Factories
#include "Player.hpp"
#include "IMonster.hpp"

#include "LoadMonsters.hpp"

class Game {
    public:
        Game(Room &room);
        ~Game();
        void loop();

    private:
        void initGame();
        void updateSystems(float const &timePassed);

        Room &_room;
        Coordinator _coordinator;
        std::map<MonsterType, std::shared_ptr<IMonster>> _monsterCreators;
        std::list<void *> _monsterLibs;
        bool _quit;
};