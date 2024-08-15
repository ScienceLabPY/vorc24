#include <core/hardware.hpp>
#include <device/input/InputTypes.hpp>
#include <controller/BallCollectorController.hpp>

using namespace sl_core;

BallCollectorController::BallCollectorController(EventBus *eventBus)
    : BaseController(eventBus, "BallCollector", 4096, 2),
      m_intakeMotor(MOTOR3_PIN_PWM, MOTOR3_PIN_DIR, MOTOR3_PIN_ENC_A, MOTOR3_PIN_ENC_B, MOTOR3_CHANNEL)
{
}

void BallCollectorController::initialize()
{
    eventBus->subscribe(
        EventType::GAMEPAD_EVENT,
        [this](const Event &event)
        {
            this->handleEvent(event);
        });
}

void BallCollectorController::handleEvent(const Event &event)
{
    const auto& inputData = dynamic_cast<const InputData&>(event.data);
    // Process gamepad input and control intake motor
    if (inputData.gamepadData.buttonA)
    {
        m_intakeMotor.setSpeed(1.0); // Start intake
    }
    else if (inputData.gamepadData.buttonB)
    {
        m_intakeMotor.setSpeed(-1.0); // Reverse intake
    }
    else
    {
        m_intakeMotor.setSpeed(0.0); // Stop intake
    }
}

void BallCollectorController::_run()
{
    while (true)
    {
        // Perform any continuous ball collector operations
        vTaskDelay(pdMS_TO_TICKS(20)); // 50Hz update rate
    }
}
