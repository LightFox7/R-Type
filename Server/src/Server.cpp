/*
** EPITECH PROJECT, 2020
** Server.cpp
** File description:
** Server.cpp
*/

#include <iostream>
#include "Server.hpp"

Server::Server(const std::string &ip, int port) : sock(ip, port), manager(sock)
{
    std::thread([&](){
        manager.checkPlayerTimestamp();
    }).detach();
}

Server::~Server()
{

}

void Server::loop()
{
    std::pair<std::string, Response::clientInfo> message;

    while (1) {
        message = sock.receive();
        dispatchRequest(message);
    }
}

void Server::dispatchRequest(std::pair<std::string, Response::clientInfo> info)
{
    Response::ResponseStruct *response;

    response = (Response::ResponseStruct *)info.first.c_str();

    for (auto it = manager.ListRoom.begin(); it != manager.ListRoom.end(); it++) {
        if ((*it)->quit == true) {
            manager.ListRoom.erase(it);
            break;
        }
    }
    if (response->code == Response::RoomCode::Connection)
        manager.connected(response, info.second);
    if (response->code == Response::RoomCode::CreateRoom)
        manager.createRoom(response, info.second);
    if (response->code == Response::RoomCode::Ready)
        manager.setPlayerReady(response, info.second);
    if (response->code == Response::GameCode::Input || response->code == Response::RoomCode::LeaveRoom)
        manager.transferEvent(response, info.second);
    if (response->code == Response::RoomCode::WaitList)
        manager.listRoom(response, info.second);
    if (response->code == Response::RoomCode::JoinRoom)
        manager.joinRoom(response, info.second);
}