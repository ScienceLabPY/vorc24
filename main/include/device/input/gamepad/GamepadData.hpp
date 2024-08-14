#ifndef GAMEPAD_DATA_HPP
#define GAMEPAD_DATA_HPP

namespace sl_core
{
    struct GamepadData
    {
        float leftStickX;
        float leftStickY;
        float rightStickX;
        float rightStickY;
        float leftTrigger;
        float rightTrigger;
        bool buttonTriangle;
        bool buttonCircle;
        bool buttonCross;
        bool buttonSquare;
        bool leftBumper;
        bool rightBumper;
        bool leftStickClick;
        bool rightStickClick;
        bool dPadUp;
        bool dPadDown;
        bool dPadLeft;
        bool dPadRight;
        bool start;
        bool select;
        bool mode;
    };
}

#endif // GAMEPAD_DATA_HPP