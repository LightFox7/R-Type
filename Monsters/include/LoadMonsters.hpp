/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** LoadMonsters
*/

#pragma once

#include <map>
#include <list>
#include <memory>
#include <cstring>

#if __linux__
    #include <dlfcn.h>
    #include <experimental/filesystem>
#endif

#include "IMonster.hpp"

class LoadMonsters {
public:
    static void loadMonsters(std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators, std::list<void *> &monsterLibs);
    static void loadMonster(std::string const &path, std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators, std::list<void *> &monsterLibs);
    static void unloadMonsters(std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators, std::list<void *> &monsterLibs);
};
