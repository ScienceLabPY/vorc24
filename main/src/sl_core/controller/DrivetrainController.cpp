#include <core/hardware.hpp>
#include <core/event/EventBus.hpp>
#include <controller/DrivetrainControlller.hpp>
using namespace sl_core;

DrivetrainController::DrivetrainController(EventBus *eventBus)
    : BaseController(eventBus, "Drivetrain", 4096, 2)
{
}

void DrivetrainController::initialize()
{
    eventBus->subscribe(
        EventType::GAMEPAD_EVENT,
        [this](const Event &event)
        {
            this->handleEvent(event);
        });
    leftMotor = new HDMotor(
        MOTOR1_PIN_PWM,
        MOTOR1_PIN_DIR,
        MOTOR1_PIN_ENC_A,
        MOTOR1_PIN_ENC_B,
        MOTOR1_CHANNEL);
    rightMotor = new HDMotor(
        MOTOR2_PIN_PWM,
        MOTOR2_PIN_DIR,
        MOTOR2_PIN_ENC_A,
        MOTOR2_PIN_ENC_B,
        MOTOR2_CHANNEL);
}

void DrivetrainController::handleEvent(const Event &event)
{
    const GamepadData &gamepadData = *static_cast<GamepadData *>(event.data);
    // implement drivetrain control based on gamepad input

    // Implement arcade drive
    float throttle = gamepadData.leftStickY;
    float turn = gamepadData.rightStickX;

    // Calculate motor speeds using arcade drive algorithm
    float leftSpeed = throttle + turn;
    float rightSpeed = throttle - turn;

    // Normalize speeds if they exceed -1.0 to 1.0 range
    float maxSpeed = std::max(std::abs(leftSpeed), std::abs(rightSpeed));
    if (maxSpeed > 1.0f)
    {
        leftSpeed /= maxSpeed;
        rightSpeed /= maxSpeed;
    }

    // Set motor speeds
    leftMotor->setSpeed(leftSpeed);
    rightMotor->setSpeed(rightSpeed);
}

void DrivetrainController::_run()
{
    // example of a continuous drivetrain operation
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(10)); // 100Hz update rate
    }
}