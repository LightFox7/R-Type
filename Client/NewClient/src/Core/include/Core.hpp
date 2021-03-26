#pragma once

#include <memory>
#include <list>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "Exception.hpp"
#include "Structs.hpp"
#include "RessourceManager.hpp"
#include "Input.hpp"
#include "Options.hpp"
#include "Response.hpp"
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class MainMenu;

static const std::string gamename = "Game";

class Core {
    public:
        Core(const std::string &ip, int port);
        ~Core();

        void receive();

        void launch();
        void playFrame(sf::FloatRect const &view = {0, 0, 1920, 1080});
        void getResizeFactor();
        void applyOptions(Options const &newoptions, bool newwindow = false);
        void drawText(const sf::Font &font, const std::string &message, int basesize, mystructs::vector2d<int> pos, const sf::Color &color, float outlinethickness, const sf::Color &outlinecolor, bool viewindependant = false);
        void drawText(sf::Text &text, const std::string &message, int basesize, mystructs::vector2d<int> pos, const sf::Color &color, float outlinethickness, const sf::Color &outlinecolor, bool viewindependant = false);
        void drawRect(const mystructs::vector2d<float> &pos, const mystructs::vector2d<float> &size, const sf::Color &color, float outlinethickness, const sf::Color &outlinecolor, bool viewindependant = false);
        void drawSprite(sf::Sprite &sprite, bool viewindependant = false);

        bool _quit;
        Options options;
        sf::RenderWindow window;
        mystructs::vector2d<float> resizefactor;
        RessourceManager ressources;
        Input input;

        boost::asio::io_service io_service;
		udp::endpoint receiver_endpoint;
        udp::endpoint who;
        udp::socket socket;
        std::list<Response::ResponseStruct> listCommand;
        std::mutex _mutex;
        int port;
        int id_room;

    private:
        int _framesthisec;
        int _framestodisplay;
        std::chrono::steady_clock::time_point _framecountclock;
};

#include "MainMenu.hpp"