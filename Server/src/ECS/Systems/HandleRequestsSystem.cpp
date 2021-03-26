/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** HandleRequestsSystem
*/

#include "HandleRequestsSystem.hpp"

HandleRequestsSystem::HandleRequestsSystem()
{
}

HandleRequestsSystem::~HandleRequestsSystem()
{
}

void HandleRequestsSystem::update(Room &room, Coordinator &coordinator)
{
    Client client;
    Response::ResponseStruct request{};

    while (room.listEvent.begin() != room.listEvent.end()) {
        client = room.listEvent.front().first;
        request = room.listEvent.front().second;
        room.listEvent.pop_front();
        if (request.code == Response::RoomCode::LeaveRoom) {
            for (auto entity : coordinator.getEntities())
                if (coordinator.hasComponent<PlayerId>(entity) && coordinator.getComponent<PlayerId>(entity) == client.getId())
                    coordinator.removeEntity(room, entity);
            for (auto it = room.clients.begin(); it != room.clients.end(); ++it) {
                if (it->getId() == client.getId()) {
                    room.clients.erase(it);
                    if (room.clients.size() > 0)
                        room.sendAllLeave(client);
                    else {
                        room.sendLeave(client);
                        room.quit = true;
                    }
                    break;
                }
            }
        }
        if (request.code == Response::GameCode::Input) {
            for (auto &it : room.clients) {
                if (it.getId() == client.getId()) {
                    it.beforeInput = it.actualInput;
                    it.actualInput = *((Response::ClientInputs *)(request.event));
                }
            }
        }
    }
}