#include <core/hardware.hpp>
#include <device/input/InputTypes.hpp>
#include <controller/WhiteBallDoorController.hpp>

using namespace sl_core;

WhiteBallDoorController::ShootingWhiteBallDoorController(EventBus *eventBus): 
    BaseController(eventBus, "WhiteBallDoorController", 4096, 2),
    doorServo(SERVO2_PINPWM)
{
    doorServo->setAngle(135);
}

void WhiteBallDoorController::initialize() {
    eventBus->subscribe(
        EventType::GAMEPAD_EVENT,
        [this](const Event &event) {
            this->handleEvent(event);
        }
    )
}

void WhiteBallDoorController::handleEvent(const Event &event)
{
    const auto& inputData = dynamic_cast<const InputData&> (event.data);

    if (inputData.gamepadData.buttonY)
    {
        doorServo->setAngle(45);
    }
}

void WhiteBallDoorController::_run() {
    while (true)
    {
        vTaskDelay(psMS_TO_TICKS(20));
    }
}