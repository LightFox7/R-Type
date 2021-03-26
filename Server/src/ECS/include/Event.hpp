/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-ugo.levi-cescutti
** File description:
** Event
*/

#pragma once

#include <any>
#include <unordered_map>

#include "Types.hpp"

class Event
{
	public:
		Event(EventId const &type);
		~Event();
		template<typename T>
		void SetParam(ParamId id, T value);
		template<typename T>
		T GetParam(ParamId id);
		EventId GetType() const;

	private:
		EventId _type;
		std::unordered_map<ParamId, std::any> _data;
};

template<typename T>
void Event::SetParam(ParamId id, T value)
{
    _data[id] = value;
}

template<typename T>
T Event::GetParam(ParamId id)
{
    return std::any_cast<T>(_data[id]);
}