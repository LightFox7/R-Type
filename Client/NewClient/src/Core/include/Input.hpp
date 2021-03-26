/*
** EPITECH PROJECT, 2020
** localgame
** File description:
** Input
*/

#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Structs.hpp"

class Input {
    public:
        Input();
        ~Input();
        void handleInput(sf::RenderWindow &window);
        bool isKeyPressed(sf::Keyboard::Key key);
        bool isKeyJustPressed(sf::Keyboard::Key key);
        bool isKeyReleased(sf::Keyboard::Key key);
        bool isMouseButtonPressed(sf::Mouse::Button button);
        bool isMouseButtonJustPressed(sf::Mouse::Button button);
        bool isMouseButtonReleased(sf::Mouse::Button button);
        int getMouseWheelDelta(void);
        bool isTextEntered(void);
        sf::Uint32 getKeyEntered(void);
        mystructs::vector2d<int> getMousePos(void);

        std::vector<bool> _pressedkeys;
        std::vector<bool> _pressedkeysbefore;
        std::vector<bool> _pressedmouse;
        std::vector<bool> _pressedmousebefore;
        int _mousewheeldelta;
        bool _keythisframe;
        sf::Uint32 _keyentered;
        mystructs::vector2d<int> _mousepos;
};
