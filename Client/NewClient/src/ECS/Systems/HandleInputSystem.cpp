/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** HandleInputSystem
*/

#include "HandleInputSystem.hpp"

HandleInputSystem::HandleInputSystem()
{
}

HandleInputSystem::~HandleInputSystem()
{
}

void HandleInputSystem::update(Core &core)
{
    Response::ResponseStruct data{};
    Response::ClientInputs inputs;

    if (core.input.isKeyPressed(sf::Keyboard::Up))
        inputs.up = true;
    if (core.input.isKeyPressed(sf::Keyboard::Down))
        inputs.down = true;
    if (core.input.isKeyPressed(sf::Keyboard::Left))
        inputs.left = true;
    if (core.input.isKeyPressed(sf::Keyboard::Right))
        inputs.right = true;
    if (core.input.isKeyReleased(sf::Keyboard::Space))
        inputs.shoot = true;

    data.code = Response::GameCode::Input;
    data.roomId = core.id_room;
    std::strcpy(data.pseudo, "UgoLeBG");
    std::strcpy(data.roomName, "RoomDesBG");
    std::strcpy(data.password, "MdpDesBG");
    std::memset(data.event, 0, sizeof(data.event));
    std::memcpy(data.event, &inputs, sizeof(inputs));
    core.socket.send_to(boost::asio::buffer((char *)&data, sizeof(data)), core.receiver_endpoint);
}