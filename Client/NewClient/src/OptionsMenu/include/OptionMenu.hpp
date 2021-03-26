#pragma once

#include "Core.hpp"

class RectButton;
class Button;

class OptionMenu {
    public:
        OptionMenu(Core &core);
        ~OptionMenu();
        void loop();
        void draw();

    private:
        enum buttonIdxs {
            APPLY,
            BACK,
            FULLSCREENRIGHT,
            FULLSCREENLEFT,
            VSYNCRIGHT,
            VSYNCLEFT,
            ALIASINGRIGHT,
            ALIASINGLEFT,
            FRAMERATERIGHT,
            FRAMERATELEFT,
            RESOLUTIONRIGHT,
            RESOLUTIONLEFT,
            PRINTFPSRIGHT,
            PRINTFPSLEFT,
            MASTERRIGHT,
            MASTERLEFT,
            BGMRIGHT,
            BGMLEFT,
            SFXRIGHT,
            SFXLEFT
        };
        void pressAliasingRight();
        void pressAliasingLeft();
        void pressFramerateRight();
        void pressFramerateLeft();
        void pressResolutionRight();
        void pressResolutionLeft();
        void pressMasterRight();
        void pressMasterLeft();
        void pressBgmRight();
        void pressBgmLeft();
        void pressSfxRight();
        void pressSfxLeft();
        Core &_core;
        Options _options;
        sf::Sprite menuBackGround;
        std::vector<std::shared_ptr<Button>> _buttons;
};

#include "Button.hpp"
#include "RectButton.hpp"