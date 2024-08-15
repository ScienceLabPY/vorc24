#ifndef GAMEPAD_HPP
#define GAMEPAD_HPP

#include "../IDeviceInput.hpp"
#include "GamepadData.hpp"
#include <PS2X_lib.h>

namespace sl_core
{
    class Gamepad : public IDeviceInput
    {
    public:
        Gamepad();
        InputType getType() const override;
        InputData read() override;

    private:
        PS2X ps2x;
        
    };
}

#endif // GAMEPAD_HPP