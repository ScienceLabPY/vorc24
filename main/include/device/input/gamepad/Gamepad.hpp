#ifndef GAMEPAD_HPP
#define GAMEPAD_HPP

#include "../IDeviceInput.hpp"
#include "GamepadData.hpp"

namespace sl_core
{
    class Gamepad : public IDeviceInput
    {
    public:
        Gamepad();
        InputType getType() const override;
        InputData read() override;

    private:
    };
}

#endif // GAMEPAD_HPP