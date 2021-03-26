/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Event
*/

#include "Event.hpp"

Event::Event(EventId const &type) : _type(type)
{
}

Event::~Event()
{
}

EventId Event::GetType() const
{
    return _type;
}