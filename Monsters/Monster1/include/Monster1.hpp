/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Monster1
*/

#pragma once

#include "IMonster.hpp"

class Monster1 : public IMonster {
public:
    Monster1();
    ~Monster1();
    MonsterType getId();
    bool isBoss();
    std::map<ComponentType, std::any> create();

protected:
private:
    int time = 10000;
};

extern "C" {
    IMonster *makermonster() {
        return new Monster1();
    }
}