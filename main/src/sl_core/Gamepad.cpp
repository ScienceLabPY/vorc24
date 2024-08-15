#include <device/input/gamepad/Gamepad.hpp>
using namespace sl_core;

Gamepad::Gamepad()
{
}

Gamepad::~Gamepad()
{
}

void Gamepad::update()
{
    this->data->leftStickY = ps2x.Analog(PSS_LY);
    this->data->rightStickY = ps2x.Analog(PSS_RY);
    this->data->start = ps2x.
}

InputType Gamepad::getType()
{
    return InputType::GAMEPAD;
}

GamepadData Gamepad::getData()
{
    return data;
}