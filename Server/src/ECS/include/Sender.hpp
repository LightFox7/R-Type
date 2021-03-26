/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Sender
*/

#pragma once

#include "Coordinator.hpp"

class Sender {
    public:
        static void sendEntity(Coordinator &coordinator, Entity const &entity, EntityType const &type, std::any id, std::map<ComponentType, std::any> components);
        static void sendComponents(Coordinator &coordinator, Entity const &entity, std::map<ComponentType, std::any> toSend);
        static void sendDestroyEntity(Coordinator &coordinator, Entity const &entity);
};
