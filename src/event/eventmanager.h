#pragma once

#include <unordered_map>
#include <vector>
#include "event/event.h"
#include "event/eventlistener.h"
#include "utils/SafeQueue.h"

class EventManager
{
public:
	EventManager(const EventManager&) = delete;
	EventManager(EventManager&&) = delete;
	void operator=(const EventManager&) = delete;
	void operator=(EventManager&&) = delete;

	static void AddListener(IEventListener* listener, uint32_t eventId);
	static void RemoveListener(IEventListener* listener, uint32_t eventId);
	static void Dispatch(uint32_t eventId, void* payload = nullptr);
	static void PullEvents();
private:
	EventManager();
	static std::unordered_map<uint32_t, std::vector<IEventListener*>> s_eventListeners;
	static SafeQueue<Event> s_eventQueue;
};
