/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Game
*/

#include "Game.hpp"

static const std::map<char const *, char const *> texturesToLoad =
{
    {"r-typesheet1", "assets/r-typesheet1.gif"},
    {"r-typesheet2", "assets/r-typesheet2.gif"},
    {"r-typesheet3", "assets/r-typesheet3.gif"},
    {"r-typesheet5", "assets/r-typesheet5.gif"},
    {"r-typesheet7", "assets/r-typesheet7.gif"},
    {"r-typesheet8", "assets/r-typesheet8.gif"},
    {"r-typesheet9", "assets/r-typesheet9.gif"},
    {"r-typesheet10", "assets/r-typesheet10.gif"},
    {"r-typesheet11", "assets/r-typesheet11.gif"},
    {"r-typesheet12", "assets/r-typesheet12.gif"},
    {"r-typesheet13", "assets/r-typesheet13.gif"},
    {"r-typesheet14", "assets/r-typesheet14.gif"},
    {"r-typesheet16", "assets/r-typesheet16.gif"},
    {"r-typesheet17", "assets/r-typesheet17.gif"},
    {"r-typesheet18", "assets/r-typesheet18.gif"},
    {"r-typesheet19", "assets/r-typesheet19.gif"},
    {"r-typesheet20", "assets/r-typesheet20.gif"},
    {"r-typesheet21", "assets/r-typesheet21.gif"},
    {"r-typesheet22", "assets/r-typesheet22.gif"},
    {"r-typesheet23", "assets/r-typesheet23.gif"},
    {"r-typesheet24", "assets/r-typesheet24.gif"},
    {"r-typesheet25", "assets/r-typesheet25.gif"},
    {"r-typesheet26", "assets/r-typesheet26.gif"},
    {"r-typesheet27", "assets/r-typesheet27.gif"},
    {"r-typesheet28", "assets/r-typesheet28.gif"},
    {"r-typesheet29", "assets/r-typesheet29.gif"},
    {"r-typesheet30", "assets/r-typesheet30.gif"},
    {"r-typesheet31", "assets/r-typesheet31.gif"},
    {"r-typesheet32", "assets/r-typesheet32.gif"},
    {"r-typesheet33", "assets/r-typesheet33.gif"},
    {"r-typesheet34", "assets/r-typesheet34.gif"},
    {"r-typesheet35", "assets/r-typesheet35.gif"},
    {"r-typesheet36", "assets/r-typesheet36.gif"},
    {"r-typesheet37", "assets/r-typesheet37.gif"},
    {"r-typesheet38", "assets/r-typesheet38.gif"},
    {"r-typesheet39", "assets/r-typesheet39.gif"},
    {"r-typesheet40", "assets/r-typesheet40.gif"},
    {"r-typesheet41", "assets/r-typesheet41.gif"},
    {"r-typesheet42", "assets/r-typesheet42.gif"},
    {"r-typesheet43", "assets/r-typesheet43.gif"},
    {"r-typesheet44", "assets/r-typesheet44.gif"},
    {"starfield", "assets/starfield.png"}
};

Game::Game(Core &core) : _core(core), _coordinator(Coordinator(core))
{
    for (auto it : texturesToLoad) {
        _core.ressources.addTexture(it.first, it.second);
    }
    initSystems();
    LoadMonsters::loadMonsters(_monsterCreators, _monsterLibs);
    _core.ressources.addMusic("game-music", "assets/game-music.ogg");
    _core.ressources.addSound("normal-shot", "assets/normal-shot.ogg");
    _core.ressources.addSound("explosion1", "assets/explosion1-effect.ogg");
}

void Game::initSystems()
{
    _coordinator.AddSystem<SpeedApplicationSystem>(SpeedApplicationSystem());
    _coordinator.AddSystem<DrawSystem>(DrawSystem());
    _coordinator.AddSystem<HandleInputSystem>(HandleInputSystem());
    _coordinator.AddSystem<NetworkHandlerSystem>(NetworkHandlerSystem());
    _coordinator.AddSystem<AnimationSystem>(AnimationSystem());
}

Game::~Game()
{
    for (auto it : texturesToLoad) {
        _core.ressources.removeTexture(it.first);
    }
    LoadMonsters::unloadMonsters(_monsterCreators, _monsterLibs);
    _core.ressources.removeMusic("game-music");
    _core.ressources.removeSound("normal-shot");
    _core.ressources.removeSound("explosion1");
}

void Game::loop()
{
    bool quit = false;
    std::chrono::steady_clock::time_point saveTime = std::chrono::steady_clock::now();
    float timePassed = 0;

    _core.applyOptions(_core.options);
    if (_core.ressources.isMusicLoaded("game-music")) {
        _core.ressources.getMusic("game-music")->setLoop(true);
        _core.ressources.getMusic("game-music")->play();
    }
    while (!quit && !_core._quit && _core.window.isOpen()) {
        if (_core.input.isKeyPressed(sf::Keyboard::Escape))
            quit = true;
        updateSystems(timePassed);
        _core.playFrame({0, 0, 854, 480});
        timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - saveTime).count();
        saveTime = std::chrono::steady_clock::now();
    }
    if (_core.ressources.isMusicLoaded("game-music"))
        _core.ressources.getMusic("game-music")->stop();
}

void Game::updateSystems(float const &timePassed)
{
        std::shared_ptr<DrawSystem> drawSystem = _coordinator.getSystem<DrawSystem>();
        std::shared_ptr<SpeedApplicationSystem> speedApplicationSystem = _coordinator.getSystem<SpeedApplicationSystem>();
        std::shared_ptr<HandleInputSystem> handleInputSystem = _coordinator.getSystem<HandleInputSystem>();
        std::shared_ptr<NetworkHandlerSystem> networkHandlerSystem = _coordinator.getSystem<NetworkHandlerSystem>();
        std::shared_ptr<AnimationSystem> animationSystem = _coordinator.getSystem<AnimationSystem>();

        networkHandlerSystem->update(_coordinator, _core, _monsterCreators);
        speedApplicationSystem->update(_coordinator, timePassed);
        handleInputSystem->update(_core);
        animationSystem->update(_coordinator, timePassed);
        drawSystem->update(_coordinator, _core, timePassed);
}