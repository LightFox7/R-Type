/*
** EPITECH PROJECT, 2020
** IUdp.hpp
** File description:
** IUdp.hpp
*/

#ifndef __IUDP__
#define __IUDP__

#include <string>
#include "Response.hpp"

class IUdp
{
    public:
        virtual void connect(const std::string &str) = 0;
        virtual std::pair<std::string, Response::clientInfo> receive() = 0;
        virtual void send(const std::string &str) = 0;
        virtual void disconnect() = 0;
};

#endif