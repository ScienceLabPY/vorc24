#include <Arduino.h>
#include <device/input/switch/LimitSwitch.hpp>
using namespace sl_core;

LimitSwitch::LimitSwitch(int switchPin)
{
    this->switchPin = switchPin;
}

LimitSwitch::~LimitSwitch()
{
}

InputType LimitSwitch::getType() const
{
    return InputType::LIMIT_SWITCH;
}

InputData LimitSwitch::read()
{
    InputData data;
    data.limitSwitchData.isPressed = digitalRead(switchPin) == HIGH;
    return data;
}

