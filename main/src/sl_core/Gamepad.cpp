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
}

InputType Gamepad::getType()
{
    return InputType::GAMEPAD;
}

GamepadData Gamepad::getData()
{
    return data;
}