/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Game
*/

#include "Game.hpp"

Game::Game(Room &room) : _room(room), _coordinator(room)
{
    this->_quit = false;
    LoadMonsters::loadMonsters(_monsterCreators, _monsterLibs);
    _coordinator.AddSystem<SpeedApplicationSystem>(SpeedApplicationSystem());
    _coordinator.AddSystem<HandleInputSystem>(HandleInputSystem());
    _coordinator.AddSystem<GenerateShotSystem>(GenerateShotSystem(_coordinator));
    _coordinator.AddSystem<HandleRequestsSystem>(HandleRequestsSystem());
    _coordinator.AddSystem<HandleCollisionSystem>(HandleCollisionSystem(_coordinator));
    _coordinator.AddSystem<DestroySystem>(DestroySystem());
    _coordinator.AddSystem<HandleMonsterSpeed>(HandleMonsterSpeed(_coordinator));
    _coordinator.AddSystem<GenerateMonstersSystem>(GenerateMonstersSystem());
}

Game::~Game()
{
    LoadMonsters::unloadMonsters(_monsterCreators, _monsterLibs);
}

void Game::initGame()
{
    for (auto it : _room.clients) {
        Player::create(_coordinator, it.getId(), {100, (float)(125.0 + (float)(it.getId()) * 50.0)});
    }
}

void Game::loop()
{
    initGame();
    std::chrono::steady_clock::time_point saveTime = std::chrono::steady_clock::now();
    float timePassed = 0;

    while (!this->_quit) {
        updateSystems(timePassed);
        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - saveTime).count() < 17);
        timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - saveTime).count();
        saveTime = std::chrono::steady_clock::now();
    }
    this->_quit = false;
}

void Game::updateSystems(float const &timePassed)
{
        std::shared_ptr<SpeedApplicationSystem> speedApplicationSystem = _coordinator.getSystem<SpeedApplicationSystem>();
        std::shared_ptr<HandleInputSystem> handleInputSystem = _coordinator.getSystem<HandleInputSystem>();
        std::shared_ptr<HandleRequestsSystem> handleRequestsSystem = _coordinator.getSystem<HandleRequestsSystem>();
        std::shared_ptr<HandleCollisionSystem> collisionSystem = _coordinator.getSystem<HandleCollisionSystem>();
        std::shared_ptr<DestroySystem> destroySystem = _coordinator.getSystem<DestroySystem>();
        std::shared_ptr<HandleMonsterSpeed> monsterspeed = _coordinator.getSystem<HandleMonsterSpeed>();
        std::shared_ptr<GenerateMonstersSystem> monsterGenerator = _coordinator.getSystem<GenerateMonstersSystem>();

        handleRequestsSystem->update(_room, _coordinator);
        if (_room.quit) {
            this->_quit = true;
            return;
        }
        monsterGenerator->update(_coordinator, _monsterCreators, timePassed);
        monsterspeed->update(_coordinator, timePassed);
        collisionSystem->update(_coordinator, _room);
        destroySystem->update(_coordinator, _room, timePassed);
        handleInputSystem->update(_coordinator, _room);
        speedApplicationSystem->update(_coordinator, _room, timePassed);
}