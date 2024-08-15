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
    GamepadData *gamepadData = (GamepadData *)event.data;
    // implement drivetrain control based on gamepad input
    // e.g. leftMotor->setSpeed(gamepadData->leftStickY);

    double x = -gamepadData->rightStickX;
    double y = -gamepadData->leftStickY;
    double hypotenuse = std::sqrt(x * x + y * y);
    double angleRadians = std::acos(std::abs(x) / hypotenuse);
    double angleDegrees = angleRadians * 180 / M_PI;
    double turnCoefficient = -1 + (angleDegrees / 90) * 2;
    double turnValue = turnCoefficient * std::abs(std::abs(y) - std::abs(x));
    turnValue = std::round(turnValue * 100.0) / 100.0;  // Làm tròn đến hai chữ số thập phân
    double movementValue = std::max(std::abs(y), std::abs(x));
    double rawLeft, rawRight;
        
    if ((x >= 0 && y >= 0) || (x < 0 && y < 0)) {
        rawLeft = movementValue;
        rawRight = turnValue;
    } else {
        rawRight = movementValue;
        rawLeft = turnValue;
    }
    
    if (y < 0) {
        rawLeft = -rawLeft;
        rawRight = -rawRight;
    }
    
    double rightOut = map(rawRight, minJoystick, maxJoystick, minSpeed, maxSpeed);
    double leftOut = map(rawLeft, minJoystick, maxJoystick, minSpeed, maxSpeed);
    
    leftMotor->setSpeed(leftOut);
    rightMotor->setSpeed(rightOut);
}

void DrivetrainController::_run() {
    while (true) {
        // Perform any continuous drivetrain operations
        vTaskDelay(pdMS_TO_TICKS(10)); // 100Hz update rate
    }
}