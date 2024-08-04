#include <algorithm>
#include <core/event/EventBus.hpp>
using namespace sl_core;

EventBus &EventBus::getInstance()
{
    static EventBus instance;
    return instance;
}

void EventBus::addListener(EventType type, IEventListener<void *> *listener)
{
    // Add the listener to the list of listeners for the given event type
    listeners[type].push_back(listener);
}

void EventBus::removeListener(EventType type, IEventListener<void *> *listener)
{
    // Remove the listener from the list of listeners for the given event type
    auto &listenerList = listeners[type];
    listenerList.erase(
        std::remove(
            listenerList.begin(),
            listenerList.end(),
            listener),
        listenerList.end());
}

void EventBus::dispatch(EventType type, void *data)
{
    // Dispatch the event to all listeners for the given event type
    for (auto listener : listeners[type])
    {
        listener->onEvent(data);
    }
}