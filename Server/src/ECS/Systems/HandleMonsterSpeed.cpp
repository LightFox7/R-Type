/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** ColisionSystem
*/

#include "HandleMonsterSpeed.hpp"

HandleMonsterSpeed::HandleMonsterSpeed(Coordinator &coordinator)
{
}

HandleMonsterSpeed::~HandleMonsterSpeed()
{
}

void HandleMonsterSpeed::update(Coordinator &coordinator, float const &timePassed) {
    std::set<Entity> entities  = coordinator.getEntities();

    for (auto it1 = entities.begin(); it1 != entities.end(); ++it1) {
        if (coordinator.hasComponent<EntityType>(*it1) && coordinator.getComponent<EntityType>(*it1) == MONSTER) {
            if (coordinator.hasComponent<MyPattern>(*it1) && coordinator.hasComponent<Speed>(*it1)) {
                MyPattern &value = coordinator.getComponent<MyPattern>(*it1);
                Speed &speedvalue = coordinator.getComponent<Speed>(*it1);
                if (value.timeThisPart < value.pattern[value.actualIdx].duration){
                    value.timeThisPart += timePassed;
                    speedvalue.x = value.pattern[value.actualIdx].speed.x;
                    speedvalue.y = value.pattern[value.actualIdx].speed.y;
                    Sender::sendComponents(coordinator, *it1, {
                        {SPEED, speedvalue},
                    });
                } else {
                    value.timeThisPart = 0;
                    value.actualIdx += 1;
                    if (value.actualIdx >= value.pattern.size()) {
                        value.actualIdx = 0;
                    }
                }
            }
        }
    }
}