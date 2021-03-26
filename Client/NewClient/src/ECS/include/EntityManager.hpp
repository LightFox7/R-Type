/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** EntityManager
*/

#pragma once

#include <list>
#include <set>

#include "Types.hpp"

class EntityManager {
    public:
        EntityManager();
        ~EntityManager();
        Entity createEntity(void);
        Entity createEntity(Entity const &entity);
        void removeEntity(Entity const &id);
        std::set<Entity> getEntities(void);

    private:
        std::list<Entity> _available_ids;
        std::set<Entity> _used_ids;
};
