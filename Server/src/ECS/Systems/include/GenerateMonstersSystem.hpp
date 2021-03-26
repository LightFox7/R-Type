/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** GenerateMonstersSystem
*/

#pragma once

#include <ctime>
#include <cstdlib>

#include "Coordinator.hpp"
#include "IMonster.hpp"

class GenerateMonstersSystem : public ISystem {
    public:
        GenerateMonstersSystem();
        ~GenerateMonstersSystem();
        void update(Coordinator &coordinator, std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators, float const &timepassed);

    private:
        void generateMonster(Coordinator &coordinator, std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators);
        void generateBoss(Coordinator &coordinator, std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators);
        float timeBeforeNewMonster;
        float timeBeforeBoss;
};
