#include <core/hardware.hpp>
#include <device/input/InputTypes.hpp>
#include <controller/BallSortingController.hpp>

using namespace sl_core;

BallSortingController::BallSortingController(): 
   BaseController(eventBus, "BallSortingDoorController", 4096, 2),
   sortingServo(SERVO3_PINPWM)
{
    colorSensor = new ColorSensor();
}

void BallSortingController::initialize() {
    eventBus->subscribe(
        EventType->SENSOR_EVENT,
        [this](const Event& event) {
            this->handleEvent(event);
        }
    )
}

void BallSortingController::handleEvent(const Event& event)
{
    const auto& inputData = dynamic_cast<const InputData&> (event.data);
    if (inputData.LimitSwitchData.isPress) {
        if (colorSensor.isWhite()) {
            sortingServo.setSpeed(1);
            delay(TIME_TO_SET_ANGLE);
            sortingServo.setSpeed(0);
        }
        else {
            sortingServo.setSpeed(-1);
            delay(TIME_TO_SET_ANGLE);
            sortingServo.setSpeed(0);
        }
    }
}

void BallSortingController::_run() {
    while (true)
    {
        vTaskDelay(psMS_TO_TICKS(20));
    }
}