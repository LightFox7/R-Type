/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** room
*/

#include <iostream>
#include "front_room.hpp"

front_room::front_room(int id, int nbPlayer, bool state)
{
    _nbPlayer = nbPlayer;
    _state = state;
    roomId = id;
}

std::string front_room::getMsg()
{
    std::string str = "ID: " + std::to_string(roomId) + " " + std::to_string(getNbPlayer()) + " sur 4";
    return (str);
}

std::string front_room::getName() const
{
    return _name;
}

int front_room::getNbPlayer() const
{
    return _nbPlayer;
}

bool front_room::getState() const
{
    return _state;
}

int front_room::getRoomId()
{
    return (roomId);
}

std::string front_room::getMdp()
{
    return (mdp);
}

void front_room::setNbPlayer(int nb)
{
    _nbPlayer = nb;
}