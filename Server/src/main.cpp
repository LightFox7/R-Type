/*
** EPITECH PROJECT, 2020
** main
** File description:
** main
*/

#include <iostream>
#include "Server.hpp"

bool is_number(std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
        if (str[i] < '0' || '9' < str[i])
            return (false);
    return (true);
}

int main(int ac, char **av)
{
    try {
        if (ac != 3 || (is_number(av[2]) == false))
            throw(Exception ("Only 3 arguments required or bad argument ./r-type_server [ip] [port]"));
        Server server(av[1], std::stoi(av[2]));
        server.loop();
    } catch (Exception &e) {
        std::cout << e.what() << std::endl;
        return (84);
    }
}