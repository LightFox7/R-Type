#include "Core.hpp"

Core::Core(const std::string &ip, int port) : receiver_endpoint(boost::asio::ip::address::from_string(ip), port), socket(io_service)
{
    resizefactor = 1.0;
    _framesthisec = 0;
    _framestodisplay = 0;
    _quit = false;
    _framecountclock = std::chrono::steady_clock::now();
    options.load("options.txt");
    applyOptions(options, true);
    ressources.addFont("yoster", "assets/yoster.ttf");

    socket.open(udp::v4());
    std::thread([&](){receive();}).detach();
}

Core::~Core()
{
}

void Core::receive()
{
    std::string receive;
    Response::ResponseStruct reponse;

    while (1) {
        receive.clear();
        receive.resize(sizeof(Response::ResponseStruct));
        socket.receive_from(boost::asio::buffer(receive), who);
        reponse = *(Response::ResponseStruct *)receive.c_str();
        _mutex.lock();
        if (reponse.code == Response::RoomCode::ConnectionOk) {
            port = reponse.port;
        } else
            listCommand.push_back(reponse);
        _mutex.unlock();
    }
}

void Core::launch()
{
    Response::ResponseStruct reponse{};
    MainMenu menu(*this);

    reponse.code = Response::RoomCode::Connection;
    socket.send_to(boost::asio::buffer((char *)&reponse, sizeof(reponse)), receiver_endpoint);

    menu.loop();
}

void Core::getResizeFactor()
{
    float factorx = (float)(window.getSize().x) / base_window_sizex;
    float factory = (float)(window.getSize().y) / base_window_sizey;

    resizefactor = {factorx, factory};
}

void Core::playFrame(sf::FloatRect const &view)
{
    input.handleInput(window);
    getResizeFactor();
    _framesthisec += 1;
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _framecountclock).count() > 1000) {
        _framestodisplay = _framesthisec;
        _framesthisec = 0;
        _framecountclock = std::chrono::steady_clock::now();
    }
    if (options.printfps)
        drawText(*ressources.getFont("yoster"), std::to_string(_framestodisplay), 60, {20, 0}, sf::Color::Green, 2, sf::Color::Black, true);
    window.setView(sf::View({view.left * resizefactor.x, view.top * resizefactor.y,
    view.width * resizefactor.x, view.height * resizefactor.y}));
    window.display();
    window.clear(sf::Color::Black);
}

void Core::applyOptions(Options const &newoptions, bool newwindow)
{
    sf::ContextSettings settings;

    if (options.fullscreen != newoptions.fullscreen || !(newoptions.resolution == options.resolution)
    || newoptions.antialiasinglevel != options.antialiasinglevel || newwindow == true) {
        settings.antialiasingLevel = newoptions.antialiasinglevel;
        if (newoptions.fullscreen)
            window.create(sf::VideoMode(newoptions.resolution.x, newoptions.resolution.y), gamename, sf::Style::Fullscreen, settings);
        else
            window.create(sf::VideoMode(newoptions.resolution.x, newoptions.resolution.y), gamename, sf::Style::Close, settings);
    }
    window.setFramerateLimit(newoptions.maxframerate);
    window.setVerticalSyncEnabled(newoptions.vsync);
    options = newoptions;
    ressources.setMusicsVolume(((float)options.mastervolume/100.0) * options.bgmvolume);
    ressources.setSoundsVolume(((float)options.mastervolume/100.0) * options.effectsvolume);
    options.save("options.txt");
}

void Core::drawText(const sf::Font &font, const std::string &message, int basesize, mystructs::vector2d<int>pos, const sf::Color &color, float outlinethickness, const sf::Color &outlinecolor, bool viewindependant)
{
    const sf::View winview = window.getView();
    sf::Text text;

    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(basesize);
    if (!viewindependant)
        text.setPosition({pos.x * resizefactor.x, pos.y * resizefactor.y});
    else
        text.setPosition({(pos.x + winview.getViewport().left) * resizefactor.x, (pos.y + winview.getViewport().height) * resizefactor.y});
    text.setFillColor(color);
    text.setOutlineColor(outlinecolor);
    text.setOutlineThickness(outlinethickness);
    text.setScale(resizefactor.x, resizefactor.y);
    window.draw(text);
}

void Core::drawText(sf::Text &text, const std::string &message, int basesize, mystructs::vector2d<int>pos, const sf::Color &color, float outlinethickness, const sf::Color &outlinecolor, bool viewindependant)
{
    const sf::View winview = window.getView();

    text.setString(message);
    text.setCharacterSize(basesize);
    if (!viewindependant)
        text.setPosition({pos.x * resizefactor.x, pos.y * resizefactor.y});
    else
        text.setPosition({(pos.x + winview.getViewport().left) * resizefactor.x, (pos.y + winview.getViewport().height) * resizefactor.y});
    text.setFillColor(color);
    text.setOutlineColor(outlinecolor);
    text.setOutlineThickness(outlinethickness);
    text.setScale(resizefactor.x, resizefactor.y);
    window.draw(text);
}

void Core::drawRect(const mystructs::vector2d<float> &pos, const mystructs::vector2d<float> &size, const sf::Color &color, float outlinethickness, const sf::Color &outlinecolor, bool viewindependant)
{
    const sf::View winview = window.getView();
    sf::RectangleShape rect;

    rect.setSize({size.x, size.y});
    if (!viewindependant)
        rect.setPosition({pos.x * resizefactor.x, pos.y * resizefactor.y});
    else
        rect.setPosition({(pos.x + winview.getViewport().left) * resizefactor.x, (pos.y + winview.getViewport().height) * resizefactor.y});
    rect.setFillColor(color);
    rect.setOutlineThickness(outlinethickness);
    rect.setOutlineColor(outlinecolor);
    rect.setScale(resizefactor.x, resizefactor.y);
    window.draw(rect);
}

void Core::drawSprite(sf::Sprite &sprite, bool viewindependant)
{
    const sf::View winview = window.getView();
    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2f scale = sprite.getScale();

    if (!viewindependant)
        sprite.setPosition({pos.x * resizefactor.x, pos.y * resizefactor.y});
    else
        sprite.setPosition({(pos.x + winview.getViewport().left) * resizefactor.x, (pos.y + winview.getViewport().height) * resizefactor.y});
    sprite.setScale(resizefactor.x * scale.x, resizefactor.y * scale.y);
    window.draw(sprite);
    sprite.setScale(scale);
    sprite.setPosition(pos);
}