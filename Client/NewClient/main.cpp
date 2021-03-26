/*
** EPITECH PROJECT, 2020
** new_client
** File description:
** new_client
*/

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "Core.hpp"
#include "Response.hpp"

using boost::asio::ip::udp;

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
        Core core(av[1], std::stoi(av[2]));
        if (core.window.isOpen())
            core.launch();
	}
	catch (Exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}