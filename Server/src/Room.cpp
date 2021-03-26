/*
** EPITECH PROJECT, 2020
** Room
** File description:
** Room
*/

#include "Room.hpp"
#include "Game.hpp"
#include <map>

Room::Room(int id, const std::string &str, std::shared_ptr<AsioUdp> &network) : roomId(id), name(str), sock(network)
{
    game = nullptr;
    quit = false;
    start = false;
    game_thread = nullptr;
}

Room::Room(int id, const std::string &str, const std::string &pass, std::shared_ptr<AsioUdp> &network) : roomId(id), name(str), password(pass), sock(network)
{
    game = nullptr;
    quit = false;
    start = false;
    game_thread = nullptr;
}

Room::~Room()
{
    if (game_thread)
        game_thread->join();
}

void Room::send_to_all(Response::ResponseStruct response)
{
    for (size_t i = 0; i < clients.size(); i++) {
        sock->send(response, clients[i].getIp(), clients[i].getPort());
    }
}

bool Room::addPlayer(Client &client)
{
    std::map<int, bool> nb = {std::pair<int, bool>(1, false), std::pair<int, bool>(2, false), std::pair<int, bool>(3, false), std::pair<int, bool>(4, false)};
    int number = -1;

    if (clients.size() < 4) {
        for (size_t i = 0; i < clients.size(); i++) {
            auto it = nb.find(clients[i].getId());
            it->second = true;
        }
        for (auto lol = nb.begin(); lol != nb.end(); lol++) {
            if (lol->second == false) {
                number = lol->first;
                break;
            }
        }
        client.setId(number);
        clients.push_back(client);
        return (true);
    }
    return (false);
}

bool Room::removePlayer(Response::clientInfo info)
{
    for (auto it = clients.begin(); it != clients.end(); it++)
        if (it->getIp() == info.ip && it->getPort() == info.port) {
            clients.erase(it);
            return (true);
        }
    return (false);
}

void Room::setPlayerReady(Response::clientInfo info)
{
    Response::ResponseStruct response{};
    for (auto it = clients.begin(); it != clients.end(); it++)
        if (it->getIp() == info.ip && it->getPort() == info.port) {
            response.roomId = it->getRoom();
            std::strcpy(response.pseudo, it->getPseudo().c_str());
            response.code = Response::RoomCode::PlayerReady;
            it->setReady(true);
            send_to_all(response);
            break;
        }
}

void Room::setPlayerUnready(Response::clientInfo info)
{
    Response::ResponseStruct response{};
    for (auto it = clients.begin(); it != clients.end(); it++)
        if (it->getIp() == info.ip && it->getPort() == info.port) {
            response.roomId = it->getRoom();
            std::strcpy(response.pseudo, it->getPseudo().c_str());
            response.code = Response::RoomCode::PlayerReady;
            it->setReady(false);
            send_to_all(response);
            break;
        }
}

bool Room::allReady()
{
    for (auto it = clients.begin(); it != clients.end(); it++) {
        if (it->getReady() == false)
            return (false);
    }
    return (true);
}

void Room::launch_game()
{
    Response::ResponseStruct response{};

    response.roomId = roomId;
    response.code = Response::RoomCode::GameStart;
    send_to_all(response);
    start = true;
    game_thread = std::make_shared<boost::thread>([this]{
        game = std::make_shared<Game>(*this);
        this->game->loop();
    });
}

void Room::eventGame(Response::ResponseStruct *response, Response::clientInfo info)
{
    Client client;
    bool exist = false;

    for (size_t i = 0; i < clients.size(); i++) {
        if (clients[i].getIp() == info.ip && clients[i].getPort() == info.port) {
            exist = true;
            client = clients[i];
        }
    }
    if (exist == false)
        return;
    if (start == false && Response::RoomCode::LeaveRoom == response->code) {
        if (clients.size() - 1 > 0) {
            sendAllLeave(client);
            removePlayer(info);
        } else if (clients.size() == 1) {
            sendLeave(client);
            removePlayer(info);
            quit = true;
        }
    } else {
        listEvent.push_back(std::pair<Client, Response::ResponseStruct>(client, *response));
    }
}

int Room::getRoomId()
{
    return (roomId);
}

int Room::nbPlayer()
{
    return (clients.size());
}

std::string Room::getName()
{
    return (name);
}

std::string Room::getPassword()
{
    return (password);
}

void Room::setRoomId(int id)
{
    roomId = id;
}

void Room::setName(const std::string &str)
{
    name = str;
}

void Room::setPassword(const std::string &str)
{
    password = str;
}

void Room::sendLeave(Client client)
{
    Response::ResponseStruct retour{};

    retour.code = Response::RoomCode::RoomLeaved;
    retour.roomId = getRoomId();
    retour.port = client.getPort();
    std::strcpy(retour.pseudo, client.getPseudo().c_str());
    sock->send(retour, client.getIp(), client.getPort());
}

void Room::sendAllLeave(Client client)
{
    Response::ResponseStruct retour{};

    retour.code = Response::RoomCode::ClientLeave;
    retour.roomId = getRoomId();
    retour.port = client.getPort();
    std::strcpy(retour.pseudo, client.getPseudo().c_str());
    send_to_all(retour);
    retour.code = Response::RoomCode::RoomLeaved;
    sock->send(retour, client.getIp(), client.getPort());
}