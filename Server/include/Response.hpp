/*
** EPITECH PROJECT, 2020
** AsioUdp.hpp
** File description:
** AsioUdp.hpp
*/

#ifndef __RESPONSE__
#define __RESPONSE__

#include <string>

class Response
{
    public:
        Response() {}

        ~Response() {
            //delete info;
        }

        enum ResponseType {
            Room = 1,
            Game = 2
        };

        enum RoomCode {
            /* Client -> Server */
            Connection = 100,
            /* Server -> Client */
            ConnectionOk = 101,

            /* Client -> Server */
            CreateRoom = 102,
            /* Server -> Client */
            RoomCreated = 103,

            /* Client -> Server */
            JoinRoom = 104,
            /* Server -> Client */
            JoindedRoom = 105,

            /* Client -> Server */
            LeaveRoom = 106,
            /* Server -> Client */
            RoomLeaved = 107,

            /* Server -> Client */
            ClientLeave = 108,

            /* Client -> Server */
            DeleteRoom = 109,

            /* Client -> Server */
            Ready = 110,
            /* Server -> Client */
            PlayerReady = 111,

            /* Server -> Client */
            GameStart = 112,

            /* Client -> Server */
            Ping = 113,

            /* Client -> Server */
            WaitList = 114,
            /* Server -> Client */
            AddRoom = 115
        };

        enum GameCode {
            /* Client -> Server */
            Input = 200,
            // Server -> Client
            CreateEntity = 210,
            SetComponent = 211,
            DeleteEntity = 220,
            DeleteComponent = 221,
        };

        struct ClientInputs {
            bool left = false;
            bool right = false;
            bool up = false;
            bool down = false;
            bool shoot = false;
        };

        struct ResponseStruct {
            int code;
            int roomId;
            int nbP;
            int port;
            int running;
            char pseudo[20];
            char roomName[20];
            char password[20];
            char event[64];
        } data_t;

        struct clientInfo {
            std::string ip;
            unsigned int port;
            unsigned int time;
        } clientInfo_t;

        ResponseStruct *info;
};

#endif