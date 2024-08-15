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

    struct InputData
    {
        // This is a generic structure to hold various input data types
        union
        {
            GamepadData gamepadData;
            LimitSwitchData limitSwitchData;
            ColorSensorData colorSensorData;
            // Add other input data structures as needed
        };
    };

} // namespace sl_core

#endif // INPUT_TYPES_HPP