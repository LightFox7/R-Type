/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** EventManager
*/

#include "EventManager.hpp"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::AddListener(EventId eventId, std::function<void(Coordinator &, Event&)> const &listener)
{
    listeners[eventId].push_back(listener);
}

void EventManager::SendEvent(Coordinator &coordinator, Event& event)
{
    uint32_t type = event.GetType();

    for (auto const& listener : listeners[type]) {
        listener(coordinator, event);
    }
}

void EventManager::SendEvent(Coordinator &coordinator, EventId eventId)
{
    Event event(eventId);

    for (auto const& listener : listeners[eventId]) {
        listener(coordinator, event);
    }
}