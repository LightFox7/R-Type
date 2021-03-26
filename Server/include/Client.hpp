/*
** EPITECH PROJECT, 2020
** Client
** File description:
** Client
*/

#ifndef __CLIENT__
#define __CLIENT__

#include <string>
#include "Response.hpp"

class Client
{
    public:
        Client();
        Client(Response::ResponseStruct *reponse, Response::clientInfo info);
        ~Client();

        void setId(int nb);

        std::string &getIp()
        {
            return (ip);
        }

        void setIp(const std::string &str)
        {
            ip = str;
        }

        std::string &getPseudo()
        {
            return (pseudo);
        }

        void setPseudo(const std::string &str)
        {
            pseudo = str;
        }

        int &getRoom()
        {
            return (roomId);
        }

        void setRoom(int nb)
        {
            roomId = nb;
        }

        unsigned short getPort()
        {
            return (port);
        }

        void setPort(unsigned short nb)
        {
            port = nb;
        }

        unsigned short getTime()
        {
            return (timer);
        }

        void setTime(unsigned short nb)
        {
            timer = nb;
        }

        bool getReady()
        {
            return (ready);
        }

        void setReady(bool value)
        {
            ready = value;
        }

        int getId()
        {
            return (playerId);
        }

        Response::ClientInputs actualInput;
        Response::ClientInputs beforeInput;

    private:
        std::string ip;
        int roomId;
        std::string pseudo;
        unsigned int port;
        unsigned int timer;
        bool ready;
        int playerId;
};

#endif