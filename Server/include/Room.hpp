/*
** EPITECH PROJECT, 2020
** Room
** File description:
** Room
*/

#ifndef __ROOM__
#define __ROOM__

#include <vector>
#include <memory>
#include <string>
#include <list>
#include <boost/thread.hpp>
#include "AsioUdp.hpp"
#include "Client.hpp"

class Game;

class Room
{
    public:
        Room(int id, const std::string &str, std::shared_ptr<AsioUdp> &network);
        Room(int id, const std::string &str, const std::string &pass, std::shared_ptr<AsioUdp> &network);
        ~Room();

        void send_to_all(Response::ResponseStruct response);
        bool addPlayer(Client &client);
        bool removePlayer(Response::clientInfo info);
        void setPlayerReady(Response::clientInfo info);
        void setPlayerUnready(Response::clientInfo info);
        bool allReady();
        void launch_game();
        void eventGame(Response::ResponseStruct *response, Response::clientInfo info);

        int getRoomId();
        int nbPlayer();
        std::string getName();
        std::string getPassword();

        void setRoomId(int id);
        void setName(const std::string &str);
        void setPassword(const std::string &str);

        void sendLeave(Client client);
        void sendAllLeave(Client client);

        bool getRun() {
            return (start);
        }

        std::list<std::pair<Client, Response::ResponseStruct>> listEvent;
        std::vector<Client> clients;
        int roomId;
        std::string name;
        std::string password;
        bool quit;
        bool start;
        std::shared_ptr<Game> game;
        std::shared_ptr<boost::thread> game_thread;

    private:
        std::shared_ptr<AsioUdp> sock;
};

#include "Game.hpp"

#endif