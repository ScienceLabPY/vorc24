// InputTypes.hpp
#ifndef INPUT_TYPES_HPP
#define INPUT_TYPES_HPP

#include "gamepad/GamepadData.hpp"
#include "switch/LimitSwitchData.hpp"
#include "color/ColorSensorData.hpp"

namespace sl_core
{

    enum class InputType
    {
        GAMEPAD,
        COLOR_SENSOR,
        LIMIT_SWITCH,
        // Add other input types as needed
    };

    union InputData
    {
        GamepadData gamepadData;
        LimitSwitchData limitSwitchData;
        ColorSensorData colorSensorData;
        // Add other input data structures as needed
    };

    template<typename EventType>
    struct InputEvent {
        InputType type;
        InputData data;
    };
} // namespace sl_core

#endif // INPUT_TYPES_HPP