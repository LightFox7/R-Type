/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Monster2
*/

#pragma once

#include "IMonster.hpp"

class Monster3 : public IMonster {
public:
    Monster3();
    ~Monster3();
    MonsterType getId();
    bool isBoss();
    std::map<ComponentType, std::any> create();

protected:
private:
};

extern "C" {
    IMonster *makermonster() {
        return new Monster3();
    }
}