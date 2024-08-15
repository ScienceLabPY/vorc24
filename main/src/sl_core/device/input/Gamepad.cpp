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

    data.gamepadData.buttonA = ps2x.Button(PSB_GREEN);
    data.gamepadData.buttonB = ps2x.Button(PSB_RED);
    data.gamepadData.buttonY = ps2x.Button(PSB_PINK);

    
    data.gamepadData.leftStickY = ps2x.Analog(PSS_LY) / 128.0f - 1.0f; // Chuyển đổi từ 0-255 sang -1.0 to 1.0
    data.gamepadData.rightStickX = ps2x.Analog(PSS_RX) / 128.0f - 1.0f;

    data.gamepadData.leftTrigger = ps2x.Analog(PSAB_L2) / 255.0f;
    data.gamepadData.rightTrigger = ps2x.Analog(PSAB_R2) / 255.0f

    return data;
}