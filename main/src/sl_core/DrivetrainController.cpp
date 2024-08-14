#include <core/event/EventBus.hpp>
#include <controller/DrivetrainControlller.hpp>
using namespace sl_core;

DrivetrainController::DrivetrainController(): 
    IEventListener<GamepadData>(EventType::GAMEPAD_INPUT)
{
    this->leftMotor = new HDMotor(/*value*/);
    this->rightMotor = new HDMotor(/*value*/);
    // leftMotor = new Motor();
    // rightMotor = new Motor();
}

DrivetrainController::~DrivetrainController()
{
    delete leftMotor;
    delete rightMotor;
    // delete leftMotor;
    // delete rightMotor;
}

void DrivetrainController::onEvent(GamepadData data)
{
    // implement motor control here
    leftMotor->setSpeed(data->leftStickY);
    rightMotor->setSpeed(data->rightStickY);
}