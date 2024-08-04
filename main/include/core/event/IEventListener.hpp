#ifndef EVENT_LISTENER_HPP
#define EVENT_LISTENER_HPP

#include "core/event/EventBus.hpp"
#include "core/event/EventTypes.hpp"

namespace sl_core
{
    template <typename TData>
    class IEventListener
    {
    public:
        virtual IEventListener(EventType type)
        {
            EventBus::getInstance().subscribe(type, this);
        }
        = 0;
        virtual ~IEventListener() = default;
        virtual void onEvent(TData data) = 0;
    };
}

#endif // EVENT_LISTENER_HPP