/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** GenerateMonstersSystem
*/

#include "GenerateMonstersSystem.hpp"

GenerateMonstersSystem::GenerateMonstersSystem()
{
    std::srand(std::time(nullptr));
    timeBeforeNewMonster = 1000;
    timeBeforeBoss = 10000;
}

GenerateMonstersSystem::~GenerateMonstersSystem()
{
}

void GenerateMonstersSystem::update(Coordinator &coordinator, std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators, float const &timepassed)
{
    int nb_players = coordinator._room.clients.size();
    int nb_monsters = 0;
    std::set<Entity> entities = coordinator.getEntities();

    for (auto entity : entities) {
        if (coordinator.hasComponent<EntityType>(entity) && coordinator.getComponent<EntityType>(entity) == MONSTER)
            nb_monsters++;
    }
    if (nb_players > 0 && (nb_monsters / nb_players) < 6)
        generateMonster(coordinator, monsterCreators);
    timeBeforeNewMonster -= timepassed;
    timeBeforeBoss -= timepassed;
    if (timeBeforeNewMonster < 0 && nb_players > 0) {
        timeBeforeNewMonster = 1000 / nb_players;
        generateMonster(coordinator, monsterCreators);
    }
    if (timeBeforeBoss < 0 && nb_players > 0) {
        timeBeforeBoss = 80000 / nb_players;
        generateBoss(coordinator, monsterCreators);
    }
}

void GenerateMonstersSystem::generateMonster(Coordinator &coordinator, std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators)
{
    int nb_types_monsters = 0;
    int to_generate = 0;
    int i = 0;

    for (auto it : monsterCreators)
        if (!it.second->isBoss())
            nb_types_monsters++;
    to_generate = std::rand() % nb_types_monsters;
    for (auto it = monsterCreators.begin(); it != monsterCreators.end(); ++it) {
        if (i == to_generate && !it->second->isBoss()) {
            Entity monster = coordinator.createEntity();
            std::map<ComponentType, std::any> components = it->second->create();
            for (auto const &it2 : components) {
                coordinator.addComponent(monster, it2.first, it2.second);
            }
            coordinator.addComponent<Position>(monster, {900, (float)(std::rand() % 440 + 40.0)});
            if (coordinator.hasComponent<Position>(monster) && coordinator.hasComponent<Speed>(monster))
                Sender::sendEntity(coordinator, monster, MONSTER, it->first, {
                    {POSITION, coordinator.getComponent<Position>(monster)},
                    {SPEED, coordinator.getComponent<Speed>(monster)},
                });
            else
                Sender::sendEntity(coordinator, monster, MONSTER, it->first, {});
            break;
        }
        if (!it->second->isBoss())
            i++;
    }
}

void GenerateMonstersSystem::generateBoss(Coordinator &coordinator, std::map<MonsterType, std::shared_ptr<IMonster>> &monsterCreators)
{
    int nb_types_monsters = 0;
    int to_generate = 0;
    int i = 0;

    for (auto it : monsterCreators)
        if (it.second->isBoss())
            nb_types_monsters++;
    to_generate = std::rand() % nb_types_monsters;
    for (auto it = monsterCreators.begin(); it != monsterCreators.end(); ++it) {
        if (i == to_generate && it->second->isBoss()) {
            Entity monster = coordinator.createEntity();
            std::map<ComponentType, std::any> components = it->second->create();
            for (auto const &it2 : components) {
                coordinator.addComponent(monster, it2.first, it2.second);
            }
            coordinator.addComponent<Position>(monster, {900, 240});
            if (coordinator.hasComponent<Position>(monster) && coordinator.hasComponent<Speed>(monster))
                Sender::sendEntity(coordinator, monster, MONSTER, it->first, {
                    {POSITION, coordinator.getComponent<Position>(monster)},
                    {SPEED, coordinator.getComponent<Speed>(monster)},
                });
            else
                Sender::sendEntity(coordinator, monster, MONSTER, it->first, {});
            break;
        }
        if (it->second->isBoss())
            i++;
    }
}