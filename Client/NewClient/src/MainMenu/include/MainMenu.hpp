#pragma once

#include "Core.hpp"
#include "front_room.hpp"

//class Game;
class RectButton;
class Button;
class OptionMenu;

class MainMenu {
    public:
        MainMenu(Core &core);
        ~MainMenu();
        void loop();
        void draw();
        void playGame();
        void RoomSelection();
        void RoomCreation();
        void AddRoom(int roomId, int nbP, bool state);
        void join(int i);
        void create();
        void UpdateRoom();
        void waitingRoom();
        void leaveRoom();

    private:
        void launchOptions();
        enum buttonIdxs {
            PLAY,
            OPTIONS,
            QUIT
        };
        enum SelectionIdxs {
            CREATE,
            BACK,
            RIGHT,
            LEFT
        };
        enum WaitingIdxs {
            GO_BACK,
            LAUNCH
        };

        enum OtherIdxs {
            ROOM
        };
        Core &_core;
        sf::Sprite menuBackGround;
        std::shared_ptr<sf::Texture> menuBackTexture;
        std::vector<std::shared_ptr<Button>> _buttons;
        std::vector<std::shared_ptr<Button>> _buttonsSelection;
        std::vector<std::shared_ptr<Button>> _buttonsWaiting;
        std::vector<std::shared_ptr<Button>> _buttonsOther;
        std::vector<std::shared_ptr<front_room>> listRooms;
};

#include "Button.hpp"
#include "RectButton.hpp"
#include "OptionMenu.hpp"
#include "TextScan.hpp"
#include "Game.hpp"