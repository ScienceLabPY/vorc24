#include <core/hardware.hpp>
#include <device/input/InputTypes.hpp>
#include <controller/ShootingController.hpp>

using namespace sl_core;

ShootingController::ShootingController(EventBus *EventBus)
    : BaseController(eventBus, "ShootingController", 4096, 2),
    shootingMotor(MOTOR4_PIN_PWM, MOTOR4_PIN_DIR, MOTOR4_PIN_ENC_A, MOTOR1_PIN_ENC_B, MOTOR4_CHANNEL),
    angleServo(SERVO1_PINPWM)
{
}

void ShootingController::initialize()
{
    eventBus->subscribe(
        EventType::GAMEPAD_EVENT,
        [this] (const Event &event)
        {
            this->handleEvent(event);
        }
    );
}

void ShootingController::handleEvent(const Event &event)
{
    const auto& InputData = dynamic_cast<const InputData&>(event.getData());
    
    if (inputData.gamepadData.buttonX) {
        shootingMotor.setSpeed(1.0);
    }
    else {
        shootingMotor.setSpeed(0.0);
    }

    float speedServo = inputData.gamepadData.rightTrigger - inputData.gamepadData.leftTrigger;
    angleServo.setSpeed(speedServo);
}

void ShootingController::_run()
{
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}