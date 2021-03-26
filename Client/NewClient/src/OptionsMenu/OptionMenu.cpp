#include "OptionMenu.hpp"

OptionMenu::OptionMenu(Core &core) : _core(core)
{
    _options = _core.options;
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(400, 100), 
    mystructs::vector2d<float>(700, 100), "APPLY", sf::Color({170, 170, 170, 150}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(400, 100), 
    mystructs::vector2d<float>(700, 900), "BACK", sf::Color({170, 170, 170, 150}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(600, 250), ">", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(200, 250), "<", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(600, 325), ">", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(200, 325), "<", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(600, 450), ">", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(200, 450), "<", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(600, 600), ">", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(200, 600), "<", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(600, 750), ">", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(200, 750), "<", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(1600, 300), ">", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(1200, 300), "<", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(1600, 450), ">", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(1200, 450), "<", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(1600, 600), ">", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(1200, 600), "<", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(1600, 750), ">", sf::Color({50, 50, 50, 200}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(50, 50), 
    mystructs::vector2d<float>(1200, 750), "<", sf::Color({50, 50, 50, 200}), sf::Color::White));
}

OptionMenu::~OptionMenu()
{
}

void OptionMenu::draw()
{
    std::shared_ptr<sf::Texture> menuBackTexture = _core.ressources.getTexture("menuback");

    if (!_core.window.isOpen())
        return;
    if (menuBackTexture) {
        menuBackGround.setTexture(*_core.ressources.getTexture("menuback"));
        _core.drawSprite(menuBackGround);
    }
    for (auto it : _buttons)
        it->draw();
    _core.drawText(*_core.ressources.getFont("yoster"), _options.fullscreen ? "FULLSCREEN" : " WINDOWED", 40, {300, 250}, sf::Color::White, 2, sf::Color::Black);
    _core.drawText(*_core.ressources.getFont("yoster"), _options.vsync ? "VSYNC : ON" : "VSYNC : OFF", 40, {300, 325}, sf::Color::White, 2, sf::Color::Black);
    _core.drawText(*_core.ressources.getFont("yoster"), "ANTI-ALIASING", 40, {270, 400}, sf::Color::White, 2, sf::Color::Black);
    _core.drawText(*_core.ressources.getFont("yoster"), "X " + std::to_string(_options.antialiasinglevel), 45, {380, 450}, sf::Color::White, 2, sf::Color::Black);
    _core.drawText(*_core.ressources.getFont("yoster"), "MAX FRAMERATE", 40, {270, 550}, sf::Color::White, 2, sf::Color::Black);
    _core.drawText(*_core.ressources.getFont("yoster"), std::to_string(_options.maxframerate) + " FPS", 45, {350, 600}, sf::Color::White, 2, sf::Color::Black);
    _core.drawText(*_core.ressources.getFont("yoster"), "RESOLUTION", 40, {300, 700}, sf::Color::White, 2, sf::Color::Black);
    _core.drawText(*_core.ressources.getFont("yoster"), std::string(std::to_string(_options.resolution.x) + " X " + std::to_string(_options.resolution.y)) , 40, {290, 750}, sf::Color::White, 2, sf::Color::Black);
    _core.drawText(*_core.ressources.getFont("yoster"), "SHOW FRAMERATE", 40, {1250, 250}, sf::Color::White, 2, sf::Color::Black);
    _core.drawText(*_core.ressources.getFont("yoster"), _options.printfps ? "YES" : "NO", 45, {1390, 300}, sf::Color::White, 2, sf::Color::Black);
    _core.drawText(*_core.ressources.getFont("yoster"), "MASTER VOLUME", 40, {1270, 400}, sf::Color::White, 2, sf::Color::Black);
    _core.drawText(*_core.ressources.getFont("yoster"), std::to_string(_options.mastervolume), 45, {1390, 450}, sf::Color::White, 2, sf::Color::Black);
    _core.drawText(*_core.ressources.getFont("yoster"), "BGM VOLUME", 40, {1300, 550}, sf::Color::White, 2, sf::Color::Black);
    _core.drawText(*_core.ressources.getFont("yoster"), std::to_string(_options.bgmvolume), 45, {1390, 600}, sf::Color::White, 2, sf::Color::Black);
    _core.drawText(*_core.ressources.getFont("yoster"), "SFX VOLUME", 40, {1300, 700}, sf::Color::White, 2, sf::Color::Black);
    _core.drawText(*_core.ressources.getFont("yoster"), std::to_string(_options.effectsvolume), 45, {1390, 750}, sf::Color::White, 2, sf::Color::Black);
    _core.playFrame();
}

void OptionMenu::loop()
{
    while (!_core._quit && _core.window.isOpen()) {
        draw();
        for (auto it : _buttons)
            it->computeStatus();
        if (_buttons[BACK]->getStatus() == Button::RELEASED)
            return;
        if (_buttons[APPLY]->getStatus() == Button::RELEASED)
            _core.applyOptions(_options);
        if (_buttons[FULLSCREENLEFT]->getStatus() == Button::RELEASED || _buttons[FULLSCREENRIGHT]->getStatus() == Button::RELEASED)
            _options.fullscreen = !_options.fullscreen;
        if (_buttons[VSYNCLEFT]->getStatus() == Button::RELEASED || _buttons[VSYNCRIGHT]->getStatus() == Button::RELEASED)
            _options.vsync = !_options.vsync;
        if (_buttons[PRINTFPSLEFT]->getStatus() == Button::RELEASED || _buttons[PRINTFPSRIGHT]->getStatus() == Button::RELEASED)
            _options.printfps = !_options.printfps;
        if (_buttons[ALIASINGRIGHT]->getStatus() == Button::RELEASED)
            pressAliasingRight();
        if (_buttons[ALIASINGLEFT]->getStatus() == Button::RELEASED)
            pressAliasingLeft();
        if (_buttons[FRAMERATERIGHT]->getStatus() == Button::RELEASED)
            pressFramerateRight();
        if (_buttons[FRAMERATELEFT]->getStatus() == Button::RELEASED)
            pressFramerateLeft();
        if (_buttons[RESOLUTIONRIGHT]->getStatus() == Button::RELEASED)
            pressResolutionRight();
        if (_buttons[RESOLUTIONLEFT]->getStatus() == Button::RELEASED)
            pressResolutionLeft();
        if (_buttons[MASTERRIGHT]->getStatus() == Button::RELEASED)
            pressMasterRight();
        if (_buttons[MASTERLEFT]->getStatus() == Button::RELEASED)
            pressMasterLeft();
        if (_buttons[BGMRIGHT]->getStatus() == Button::RELEASED)
            pressBgmRight();
        if (_buttons[BGMLEFT]->getStatus() == Button::RELEASED)
            pressBgmLeft();
        if (_buttons[SFXRIGHT]->getStatus() == Button::RELEASED)
            pressSfxRight();
        if (_buttons[SFXLEFT]->getStatus() == Button::RELEASED)
            pressSfxLeft();
    }
}

void OptionMenu::pressAliasingRight()
{
    std::size_t idx = 0;

    _options.antialiasinglevel = Options::adjustantialiasing(_options.antialiasinglevel);
    for (; antialiasinglevels[idx] != _options.antialiasinglevel; idx++);
    if ((idx + 1) >= antialiasinglevels.size())
        return;
    _options.antialiasinglevel = antialiasinglevels[idx + 1];
}

void OptionMenu::pressAliasingLeft()
{
    std::size_t idx = 0;

    _options.antialiasinglevel = Options::adjustantialiasing(_options.antialiasinglevel);
    for (; antialiasinglevels[idx] != _options.antialiasinglevel; idx++);
    if (idx <= 0)
        return;
    _options.antialiasinglevel = antialiasinglevels[idx - 1];
}

void OptionMenu::pressFramerateRight()
{
    std::size_t idx = 0;

    _options.maxframerate = Options::adjustmaxframerate(_options.maxframerate);
    for (; maxframerates[idx] != _options.maxframerate; idx++);
    if ((idx + 1) >= maxframerates.size())
        return;
    _options.maxframerate = maxframerates[idx + 1];
}

void OptionMenu::pressFramerateLeft()
{
    std::size_t idx = 0;

    _options.maxframerate = Options::adjustmaxframerate(_options.maxframerate);
    for (; maxframerates[idx] != _options.maxframerate; idx++);
    if (idx <= 0)
        return;
    _options.maxframerate = maxframerates[idx - 1];
}

void OptionMenu::pressResolutionRight()
{
    std::size_t idx = 0;

    _options.resolution = Options::adjustresolution(_options.resolution);
    for (; resolutions[idx] != _options.resolution; idx++);
    if ((idx + 1) >= resolutions.size())
        return;
    _options.resolution = resolutions[idx + 1];
}

void OptionMenu::pressResolutionLeft()
{
    std::size_t idx = 0;

    _options.resolution = Options::adjustresolution(_options.resolution);
    for (; resolutions[idx] != _options.resolution; idx++);
    if (idx <= 0)
        return;
    _options.resolution = resolutions[idx - 1];
}

void OptionMenu::pressMasterRight()
{
    std::size_t idx = 0;

    _options.mastervolume = Options::adjustvolume(_options.mastervolume);
    for (; possiblevolumelevels[idx] != _options.mastervolume; idx++);
    if ((idx + 1) >= possiblevolumelevels.size())
        return;
    _options.mastervolume = possiblevolumelevels[idx + 1];
}

void OptionMenu::pressMasterLeft()
{
    std::size_t idx = 0;

    _options.mastervolume = Options::adjustvolume(_options.mastervolume);
    for (; possiblevolumelevels[idx] != _options.mastervolume; idx++);
    if (idx <= 0)
        return;
    _options.mastervolume = possiblevolumelevels[idx - 1];
}

void OptionMenu::pressBgmRight()
{
    std::size_t idx = 0;

    _options.bgmvolume = Options::adjustvolume(_options.bgmvolume);
    for (; possiblevolumelevels[idx] != _options.bgmvolume; idx++);
    if ((idx + 1) >= possiblevolumelevels.size())
        return;
    _options.bgmvolume = possiblevolumelevels[idx + 1];
}

void OptionMenu::pressBgmLeft()
{
    std::size_t idx = 0;

    _options.bgmvolume = Options::adjustvolume(_options.bgmvolume);
    for (; possiblevolumelevels[idx] != _options.bgmvolume; idx++);
    if (idx <= 0)
        return;
    _options.bgmvolume = possiblevolumelevels[idx - 1];
}

void OptionMenu::pressSfxRight()
{
    std::size_t idx = 0;

    _options.effectsvolume = Options::adjustvolume(_options.effectsvolume);
    for (; possiblevolumelevels[idx] != _options.effectsvolume; idx++);
    if ((idx + 1) >= possiblevolumelevels.size())
        return;
    _options.effectsvolume = possiblevolumelevels[idx + 1];
}

void OptionMenu::pressSfxLeft()
{
    std::size_t idx = 0;

    _options.effectsvolume = Options::adjustvolume(_options.effectsvolume);
    for (; possiblevolumelevels[idx] != _options.effectsvolume; idx++);
    if (idx <= 0)
        return;
    _options.effectsvolume = possiblevolumelevels[idx - 1];
}