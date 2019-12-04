#ifndef TICKABLE_HPP
#define TICKABLE_HPP

#include <cstdint>
#include <map>
#include <vector>
#include <mutex>
#include "logger.hpp"

class Tickable {

public:

	Tickable() = default;
	~Tickable() 
	{
		_events.clear();
	}

	//Fires every second (separate thread)
	virtual void Tick(uint64_t tick)
	{
		_currentTick = tick;

		ProcessEvents(tick);
		UnregisterEvents(tick);
	}

	virtual void ProcessEvents(uint64_t tick)
	{
		std::lock_guard<std::recursive_mutex> lg{ _mx };

		auto events = _events[tick];

		if (events.empty())
			return;

		for (auto& theEvent : events)
		{
			theEvent();
		}
	}

	virtual void UnregisterEvents(uint64_t tick)
	{
		std::lock_guard<std::recursive_mutex> lg{ _mx };

		auto _eventsAtTick = _events.find(tick);

		if (_eventsAtTick != _events.cend())
			_events.erase(_eventsAtTick);
	}

	virtual void RegisterEvent(std::function<void()> function, uint64_t tick)
	{
		std::lock_guard<std::recursive_mutex> lg{ _mx };

		_events[tick].push_back(function);
	}

	virtual void Clear()
	{
		std::lock_guard<std::recursive_mutex> lg{ _mx };

		_events.clear();
	}

	uint64_t GetTick()
	{
		return _currentTick;
	}

private:
	std::unordered_map<uint64_t, std::vector<std::function<void()>>> _events;
	std::recursive_mutex _mx;
	uint64_t _currentTick;
};

#endif