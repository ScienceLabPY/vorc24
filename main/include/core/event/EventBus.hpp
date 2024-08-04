#ifndef EVENT_BUS_HPP
#define EVENT_BUS_HPP

#include <map>
#include <vector>
#include "EventTypes.hpp"
#include "IEventListener.hpp"

namespace sl_core
{
    class EventBus
    {
    public:
        static EventBus &getInstance(); // Get the singleton instance
        void addListener(EventType type, IEventListener<void *> *listener);
        void removeListener(EventType type, IEventListener<void *> *listener);
        void dispatch(EventType type, void *data);

    private:
        EventBus() {}                                   // Private constructor to prevent instantiation
        ~EventBus() {}                                  // Private destructor to prevent deletion
        EventBus(const EventBus &) = delete;            // Delete copy constructor
        EventBus &operator=(const EventBus &) = delete; // Delete assignment operator
        std::map<EventType, std::vector<IEventListener<void *> *>> listeners;
    };
}

#endif // EVENT_BUS_HPP