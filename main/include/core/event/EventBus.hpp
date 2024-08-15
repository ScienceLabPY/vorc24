#ifndef EVENT_BUS_HPP
#define EVENT_BUS_HPP

#include <map>
#include <vector>
#include <functional>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include "EventTypes.hpp"

namespace sl_core
{
    class EventBus
    {
    public:
        using EventHandler = std::function<void(const Event&)>;

        static EventBus &getInstance(); // Get the singleton instance
        void subscribe(EventType type, EventHandler handler);
        void unsubscribe(EventType type, EventHandler handler);
        void publish(const Event &event);
    private:
        EventBus();                                     // Private constructor to prevent instantiation
        ~EventBus();                                    // Private destructor to prevent deletion
        EventBus(const EventBus &) = delete;            // Delete copy constructor
        EventBus &operator=(const EventBus &) = delete; // Delete assignment operator
        std::map<EventType, std::vector<EventHandler>> subscribers;
        SemaphoreHandle_t mutex;
    };
}

#endif // EVENT_BUS_HPP