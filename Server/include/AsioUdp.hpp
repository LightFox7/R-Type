/*
** EPITECH PROJECT, 2020
** AsioUdp.hpp
** File description:
** AsioUdp.hpp
*/

#ifndef __ASIOUDP__
#define __ASIOUDP__

#include "IUdp.hpp"
#include <boost/asio.hpp>

class AsioUdp : public IUdp
{
    public:
        AsioUdp(const std::string &ip, int port);
        ~AsioUdp();

        void connect(const std::string &str);
        std::pair<std::string, Response::clientInfo> receive();
        void send(const std::string &str);
        void send(const std::string &str, const std::string &ip, int port);
        void send(Response::ResponseStruct, const std::string &ip, int port);
        void disconnect();

    private:
        int server_port;
        boost::asio::io_context context;
        boost::asio::ip::udp::endpoint endpoint;
        boost::asio::ip::udp::socket server_socket;
        boost::asio::ip::udp::endpoint client_endpoint;
};

#endif