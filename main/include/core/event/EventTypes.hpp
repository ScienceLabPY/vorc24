#ifndef EVENT_TYPES_HPP
#define EVENT_TYPES_HPP

namespace sl_core
{
    enum class EventType {
        GAMEPAD_EVENT,
        COLOR_SENSOR_EVENT,
        LIMIT_SWITCH_EVENT,
        // Add other event types as needed
    };

    struct Event {
        EventType type;
        void *data;
        // Add any additional data fields needed for events
    };
}

#endif // EVENT_TYPES_HPP