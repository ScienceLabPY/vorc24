#include <device/input/gamepad/Gamepad.hpp>

using namespace sl_core;

Gamepad::Gamepad() {
    // Initialize gamepad communication
}

InputType Gamepad::getType() const {
    return InputType::GAMEPAD;
}

InputData Gamepad::read() {
    InputData data;
    // Read gamepad data and fill the InputData structure
    // This is just an example, replace with actual gamepad reading logic
    data.gamepadData.buttonX = true;
    data.gamepadData.buttonY = false;
    return data;
}