/*
** EPITECH PROJECT, 2020
** localgame
** File description:
** Input
*/

#include "Input.hpp"

Input::Input()
{
    _keythisframe = false;
    for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
        _pressedkeys.push_back(false);
    _pressedkeysbefore = _pressedkeys;
    for (int i = 0; i < sf::Mouse::ButtonCount; i++)
        _pressedmouse.push_back(false);
    _pressedmousebefore = _pressedmouse;
}

Input::~Input()
{
}

void Input::handleInput(sf::RenderWindow &window)
{
    _mousewheeldelta = 0;
    _keythisframe = false;
    _pressedkeysbefore = _pressedkeys;
    for (int i = 0; i < sf::Keyboard::KeyCount; i++)
        _pressedkeys[i] = false;
    _pressedmousebefore = _pressedmouse;
    for (int i = 0; i < sf::Mouse::ButtonCount; i++)
        _pressedmouse[i] = false;
    if (window.isOpen()) {
        const sf::View view = window.getView();
        _mousepos.x = (sf::Mouse::getPosition(window).x + view.getViewport().left);
        _mousepos.y = (sf::Mouse::getPosition(window).y + view.getViewport().height);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered) {
                _keythisframe = true;
                _keyentered = event.text.unicode;
            }
            if (event.type == sf::Event::MouseWheelMoved)
                _mousewheeldelta = event.mouseWheel.delta;
        }
        for (int i = 0; i < sf::Keyboard::KeyCount; i++)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i)))
                _pressedkeys[i] = true;
        for (int i = 0; i < sf::Mouse::ButtonCount; i++)
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button(i)))
                _pressedmouse[i] = true;
    }
}

bool Input::isKeyPressed(sf::Keyboard::Key key)
{
    return (_pressedkeys[key]);
}

bool Input::isKeyJustPressed(sf::Keyboard::Key key)
{
    return (_pressedkeys[key] && !_pressedkeysbefore[key]);
}

bool Input::isKeyReleased(sf::Keyboard::Key key)
{
    return (_pressedkeysbefore[key] && !_pressedkeys[key]);
}

bool Input::isMouseButtonPressed(sf::Mouse::Button button)
{
    return (_pressedmouse[button]);
}

bool Input::isMouseButtonJustPressed(sf::Mouse::Button button)
{
    return (_pressedmouse[button] && !_pressedmousebefore[button]);
}

bool Input::isMouseButtonReleased(sf::Mouse::Button button)
{
    return (_pressedmousebefore[button] && !_pressedmouse[button]);
}

int Input::getMouseWheelDelta(void)
{
    return (_mousewheeldelta);
}

bool Input::isTextEntered(void)
{
    return (_keythisframe);
}

sf::Uint32 Input::getKeyEntered(void)
{
    return (_keyentered);
}

mystructs::vector2d<int> Input::getMousePos(void)
{
    return (_mousepos);
}