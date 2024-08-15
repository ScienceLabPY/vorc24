#include <core/event/EventBus.hpp>
#include <controller/BallSortingController.hpp>
using namespace sl_core;

#define TIME_TO_SET_ANGLE 500

BallSortingController::BallSortingController(): 
    IEventListener<LimitSwitchData>(EventType::SENSOR_DATA)
{
    this->sortingServo = new Servo();
    this->colorSensor = new ColorSensor();
}

BallCollectorController::~BallCollectorController()
{
    delete this->sortingServo;
    delete this->colorSensor;
}

void BallCollectorController::onEvent(LimitSwitchData data)
{
    if (data->LimitSwitchState) {
        if (colorSensor->isWhite()) {
            servo.setSpeed(1);
            delay(TIME_TO_SET_ANGLE);
            servo.setSpeed(0);
        }
        else {
            servo.setSpeed(-1);
            delay(TIME_TO_SET_ANGLE);
            servo.setSpeed(0);
        }
    }
}