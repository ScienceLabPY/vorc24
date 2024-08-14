#include "../../include/device/input/LimitSwitch/LimitSwitch.hpp"
using namespace sl_core;

LimitSwitch::LimitSwitch(int switchPin)
{
    this->switchPin = switchPin;
}

LimitSwitch::~LimitSwitch()
{
}

void LimitSwitch::update()
{
    bool state = digitalRead(this->switchPin);
    this->data->LimitSwitchState = state;
}

InputType LimitSwitch::getType()
{
    return InputType::LIMIT_SWITCH;
}

LimitSwitchData LimitSwitch::getData()
{
    return this->data;
}