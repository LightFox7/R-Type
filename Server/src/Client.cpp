/*
** EPITECH PROJECT, 2020
** Client
** File description:
** Client
*/

#include "Client.hpp"

Client::Client()
{
}

Client::Client(Response::ResponseStruct *reponse, Response::clientInfo info)
{
    ip = info.ip;
    roomId = reponse->roomId;
    pseudo = reponse->pseudo;
    port = info.port;
    timer = info.time;
    ready = false;
}

Client::~Client()
{
}

void Client::setId(int nb)
{
    playerId = nb;
}