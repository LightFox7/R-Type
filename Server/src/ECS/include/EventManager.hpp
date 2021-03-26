/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** EventManager
*/

#pragma once

#include "Event.hpp"
#include <functional>
#include <list>
#include <unordered_map>

class Coordinator;

class EventManager {
	public:
		EventManager();
		~EventManager();
		void AddListener(EventId eventId, std::function<void(Coordinator &, Event&)> const& listener);
		void SendEvent(Coordinator &coordinator, Event& event);
		void SendEvent(Coordinator &coordinator, EventId eventId);

	private:
		std::unordered_map<EventId, std::list<std::function<void(Coordinator&, Event&)>>> listeners;
};

#include "Coordinator.hpp"