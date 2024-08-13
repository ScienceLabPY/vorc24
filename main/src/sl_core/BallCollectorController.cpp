#include <core/event/EventBus.hpp>
#include <controller/BallCollectorController.hpp>
using namespace sl_core;

BallCollectorController::BallCollectorController(): 
    IEventListener<GamepadData>(EventType::GAMEPAD_INPUT)
{
    this->intakeMotor = new HDMotor();
}

BallCollectorController::~BallCollectorController()
{
    delete this->intakeMotor;
}

void BallCollectorController::onEvent(GamepadData data)
{
    if (data->start) {
        this->intakeMotor->setSpeed(1);
    }
    else {
        this->intakeMotor->setSpeed(0);
    }
}