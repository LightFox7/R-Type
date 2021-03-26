/*
** EPITECH PROJECT, 2020
** Server.hpp
** File description:
** Server.hpp
*/

#ifndef __SERVER__
#define __SERVER__

#include "AsioUdp.hpp"
#include "RoomManager.hpp"
#include "Response.hpp"

class Server
{
    public:
        Server(const std::string &ip, int port);
        ~Server();

        void loop();
        void dispatchRequest(std::pair<std::string, Response::clientInfo> info);
        void pingClient(const std::string &str);
        void loginClient(const std::string &str);
        void pressKeyClient(const std::string &str);
        void sendResponseToClient(const std::string &str);
        void joinRoomClient(const std::string &str);
        void createRoomClient(const std::string &str);
        void setPlayerReady(const std::string &str);
    
    private:
        AsioUdp sock;
        RoomManager manager;
};

#endif