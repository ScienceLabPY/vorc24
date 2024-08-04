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
        ~Gamepad();

        void update() override;
        InputType getType() override;
        GamepadData getData();
    private:
        GamepadData data;
    };
}

#endif // GAMEPAD_HPP