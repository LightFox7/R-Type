/*
** EPITECH PROJECT, 2020
** AsioUdp.cpp
** File description:
** AsioUdp.cpp
*/

#include "AsioUdp.hpp"
#include "Response.hpp"
#include <iostream>
#include <boost/bind.hpp>

AsioUdp::AsioUdp(const std::string &ip, int port) : server_port(port), context(), endpoint(boost::asio::ip::address::from_string(ip), port), server_socket(context, endpoint), client_endpoint()
{
    context.run();
}

AsioUdp::~AsioUdp()
{
    disconnect();
}

void AsioUdp::connect(const std::string &port)
{
    if (server_socket.is_open() == true)
        return;
    server_port = std::stoi(port);
}

std::pair<std::string, Response::clientInfo> AsioUdp::receive()
{
    std::string data;
    Response::clientInfo info;

    data.resize(sizeof(Response::ResponseStruct));
    server_socket.receive_from(boost::asio::buffer(data), client_endpoint);
    info.ip = client_endpoint.address().to_string();
    info.port = client_endpoint.port();
    info.time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    return (std::make_pair(data, info));
}

void AsioUdp::send(const std::string &str)
{
    server_socket.send_to(boost::asio::buffer(str), client_endpoint);
}

void AsioUdp::send(const std::string &str, const std::string &ip, int port)
{
    boost::asio::ip::udp::endpoint client;

    client.address(boost::asio::ip::address::from_string(ip));
    client.port(port);
    server_socket.send_to(boost::asio::buffer(str), client);
}

void AsioUdp::send(Response::ResponseStruct info, const std::string &ip, int port)
{
    boost::asio::ip::udp::endpoint client;
    client.address(boost::asio::ip::address::from_string(ip));
    client.port(port);
    server_socket.send_to(boost::asio::buffer((char *)&info, sizeof(info)), client);
}

void AsioUdp::disconnect()
{
    if (server_socket.is_open() == true)
        server_socket.close();
}