/*
** EPITECH PROJECT, 2020
** RoomManager
** File description:
** RoomManager
*/

#include "RoomManager.hpp"
#include <iostream>

RoomManager::RoomManager(AsioUdp &network) : sock(&network)
{
    std::pair<bool, int> pair;

    for (int i = 0; i < 10000; i++) {
        pair = std::make_pair(false, i);
        idList.push_back(pair);
    }
}

RoomManager::~RoomManager()
{

}

void RoomManager::checkPlayerTimestamp()
{
    /*while (1) {
        mutex.lock();
    }*/
}

void RoomManager::leaveRoom(Response::ResponseStruct *response, Response::clientInfo info)
{
    bool lol = false;
    std::vector<std::unique_ptr<Room>>::iterator it;
    Client client{};
    Response::ResponseStruct retour{};

    mutex.lock();
    for (it = ListRoom.begin(); it != ListRoom.end(); it++)
        if (response->roomId == (*it)->getRoomId()) {
            lol = true;
            break;
        }
    if (lol == false) {
        mutex.unlock();
        return;
    }
    if ((*it)->removePlayer(info) == false) {
        mutex.unlock();
        return;
    }
    if ((*it)->nbPlayer() == 0) {
        ListRoom.erase(it);
        retour.code = Response::RoomCode::RoomLeaved;
        retour.roomId = (*it)->getRoomId();
        retour.port = info.port;
        std::strcpy(retour.pseudo, client.getPseudo().c_str());
        sock->send(retour, info.ip, info.port);
    } else {
        retour.code = Response::RoomCode::ClientLeave;
        retour.roomId = (*it)->getRoomId();
        retour.port = info.port;
        std::strcpy(retour.pseudo, client.getPseudo().c_str());
        (*it)->send_to_all(retour);
        retour.code = Response::RoomCode::RoomLeaved;
        sock->send(retour, info.ip, info.port);
    }
    mutex.unlock();
}

void RoomManager::joinRoom(Response::ResponseStruct *response, Response::clientInfo info)
{
    bool lol = false;
    std::vector<std::unique_ptr<Room>>::iterator it;
    Client client(response, info);
    Response::ResponseStruct retour{};

    mutex.lock();
    for (it = ListRoom.begin(); it != ListRoom.end(); it++)
        if (client.getRoom() == (*it)->getRoomId()) {
            lol = true;
            break;
        }
    if (lol == false) {
        //send au client : ERROR
        mutex.unlock();
        return;
    }
    if ((*it)->addPlayer(client) == false) {
        //send au client : ERROR
        mutex.unlock();
        return;
    }
    retour.code = Response::RoomCode::JoindedRoom;
    retour.roomId = (*it)->getRoomId();
    std::strcpy(retour.pseudo, client.getPseudo().c_str());
    retour.port = info.port;
    mutex.unlock();
    (*it)->send_to_all(retour);
}

void RoomManager::createRoom(Response::ResponseStruct *response, Response::clientInfo info)
{
    bool lol = false;
    std::vector<std::pair<bool, int>>::iterator it;
    Client client(response, info);
    Response::ResponseStruct retour{};

    mutex.lock();
    for (it = idList.begin(); it != idList.end(); it++)
        if (it->first == false) {
            lol = true;
            it->first = true;
            break;
        }
    if (lol == false) {
        //send : CREATION ROOM FAILED
        mutex.unlock();
        return;
    }
    ListRoom.push_back(std::make_unique<Room>(it->second, response->roomName, response->password, sock));
    ListRoom[ListRoom.size() - 1]->addPlayer(client);
    //send : ROOM CREATE avec id ect
    retour.code = Response::RoomCode::RoomCreated;
    retour.roomId = it->second;
    std::strcpy(retour.roomName, response->roomName);
    std::strcpy(retour.password, response->password);
    mutex.unlock();
    sock->send(retour, info.ip, info.port);
    retour.code = Response::RoomCode::JoindedRoom;
    sock->send(retour, info.ip, info.port);
}

void RoomManager::connected(Response::ResponseStruct *response, Response::clientInfo info)
{
    Response::ResponseStruct retour{};

    retour.code = Response::RoomCode::ConnectionOk;
    retour.port = info.port;
    sock->send(retour, info.ip, info.port);
}

void RoomManager::setPlayerReady(Response::ResponseStruct *response, Response::clientInfo info)
{
    bool lol = false;
    std::vector<std::unique_ptr<Room>>::iterator it;

    mutex.lock();
    for (it = ListRoom.begin(); it != ListRoom.end(); it++)
        if (response->roomId == (*it)->getRoomId()) {
            lol = true;
            break;
        }
    if (lol == false) {
        //NO room match the id
        mutex.unlock();
        return;
    }
    (*it)->setPlayerReady(info);
    if ((*it)->allReady() == true)
        (*it)->launch_game();
    mutex.unlock();
}

void RoomManager::transferEvent(Response::ResponseStruct *response, Response::clientInfo info)
{
    bool lol = false;
    std::vector<std::unique_ptr<Room>>::iterator it;

    mutex.lock();
    for (it = ListRoom.begin(); it != ListRoom.end(); it++)
        if (response->roomId == (*it)->getRoomId()) {
            lol = true;
            break;
        }
    if (lol == false) {
        mutex.unlock();
        return;
    }
    (*it)->eventGame(response, info);
    mutex.unlock();
}

void RoomManager::listRoom(Response::ResponseStruct *response, Response::clientInfo info)
{
    Response::ResponseStruct retour{};

    retour.code = Response::RoomCode::AddRoom;

    for (size_t i = 0; i < ListRoom.size(); i++) {
        retour.roomId = ListRoom[i]->roomId;
        std::strcpy(retour.roomName, ListRoom[i]->name.c_str());
        retour.nbP = ListRoom[i]->nbPlayer();
        std::strcpy(retour.password, ListRoom[i]->password.c_str());
        if (ListRoom[i]->getRun() == true)
            retour.running = 1;
        else
            retour.running = 0;
        sock->send(retour, info.ip, info.port);
    }
}