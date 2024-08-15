#include <algorithm>
#include <core/event/EventBus.hpp>
using namespace sl_core;

EventBus &EventBus::getInstance()
{
    static EventBus instance;
    return instance;
}

EventBus::EventBus()
{
    // Initialize the map of event listeners
    mutex = xSemaphoreCreateMutex();
}

EventBus::~EventBus()
{
    // Delete the mutex
    vSemaphoreDelete(mutex);
}

void EventBus::subscribe(EventType type, EventHandler handler)
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    subscribers[type].push_back(handler);
    xSemaphoreGive(mutex);
}

void EventBus::unsubscribe(EventType type, EventHandler handler)
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    auto &handlers = subscribers[type];
    handlers.erase(std::remove_if(
        handlers.begin(), handlers.end(),
        [&handler](const EventHandler &h)
        {
            return h.target_type() == handler.target_type();
        }),
        handlers.end());
    xSemaphoreGive(mutex);
}

void EventBus::publish(const Event &event)
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    auto it = subscribers.find(event.type);
    if (it != subscribers.end())
    {
        for (const auto &handler : it->second)
        {
            handler(event);
        }
    }
    xSemaphoreGive(mutex);
}