#include <core/event/EventBus.hpp>
#include <controller/WhiteBallDoorController.hpp>
using namespace sl_core;

WhiteBallDoorController::WhiteBallDoorController(): 
    IEventListener<GamepadData>(EventType::GAMEPAD_INPUT)
{
    this->doorServo = new StandardServo();
    this->state = false;
}

WhiteBallDoorController::~WhiteBallDoorController()
{
    delete this->doorServo;
}

void WhiteBallDoorController::onEvent(GamepadData data)
{
    if (data->buttonB) this->state = !this->state;
    this->doorServo.setAngle(this->state ? 45 : 135);
}