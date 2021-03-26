/*
** EPITECH PROJECT, 2020
** RoomManager
** File description:
** RoomManager
*/

#ifndef __ROOMMANAGER__
#define __ROOMMANAGER__

#include "AsioUdp.hpp"
#include "Room.hpp"
#include "Response.hpp"

class RoomManager
{
    public:
        RoomManager(AsioUdp &network);
        ~RoomManager();

        void checkPlayerTimestamp();
        void leaveRoom(Response::ResponseStruct *response, Response::clientInfo info);
        void joinRoom(Response::ResponseStruct *response, Response::clientInfo info);
        void createRoom(Response::ResponseStruct *response, Response::clientInfo info);
        void connected(Response::ResponseStruct *response, Response::clientInfo info);
        void setPlayerReady(Response::ResponseStruct *response, Response::clientInfo info);
        void transferEvent(Response::ResponseStruct *response, Response::clientInfo info);
        void listRoom(Response::ResponseStruct *response, Response::clientInfo info);

        std::vector<std::unique_ptr<Room>> ListRoom;
    private:
        std::shared_ptr<AsioUdp> sock;
        std::mutex mutex;
        std::vector<std::pair<bool, int>> idList;
        std::vector<Client> clientList;
};

#endif