/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** LoadMonsters
*/

#include "LoadMonsters.hpp"

void LoadMonsters::loadMonsters(std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators, std::list<void *> &monsterLibs)
{
    #if __linux__
        std::string path = "./monsterLibs";
        for (const auto & entry : std::experimental::filesystem::directory_iterator(path)) {
            loadMonster(entry.path(), monsterCreators, monsterLibs);
        }
    #endif
}

void LoadMonsters::loadMonster(std::string const &path, std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators, std::list<void *> &monsterLibs)
{
    #if __linux__
        void *lib = dlopen(path.c_str(), RTLD_LAZY);
        if (!lib)
            return;
        monsterLibs.push_back(lib);
        IMonster *(*mkr)() = (IMonster *(*)())dlsym(lib, "makermonster");
        if (!mkr)
            return;
        std::shared_ptr<IMonster> newmonster = std::shared_ptr<IMonster>((mkr)());
        monsterCreators.emplace(newmonster->getId(), newmonster);
    #endif
}

void LoadMonsters::unloadMonsters(std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators, std::list<void *> &monsterLibs)
{
    #if __linux__
        monsterCreators.clear();
        for (auto it : monsterLibs)
            dlclose(it);
    #endif
}