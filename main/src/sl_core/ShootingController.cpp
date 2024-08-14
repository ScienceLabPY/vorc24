#include <core/event/EventBus.hpp>
#include <controller/ShootingController.hpp>
using namespace sl_core;

ShootingController::ShootingController(): 
    IEventListener<GamepadData>(EventType::GAMEPAD_INPUT)
{
    this->shootingMotor = new HDMotor(/*value*/);
    this->angleServo = new ContinuousRotationServo(/*value*/);
}

ShootingController::~ShootingController()
{
    delete this->shootingMotor;
    delete this->angleServo;
}

void DrivetrainController::onEvent(GamepadData data)
{
    this->shootingMotor->setSpeed(data->back ? 1 : 0);
    this->angleServo->setSpeed(data->rightTrigger - data->leftTrigger);
}