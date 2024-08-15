#include <memory>
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <core/event/EventBus.hpp>
#include <core/hardware.hpp>
#include <device/input/InputMapper.hpp>
#include <controller/DrivetrainControlller.hpp>
#include <controller/BallCollectorController.hpp>

#include <device/input/gamepad/Gamepad.hpp>
#include <device/input/color/ColorSensor.hpp>
#include <device/input/switch/LimitSwitch.hpp>

using namespace sl_core;

// Input Mapper
auto &inputMapper = InputMapper<Event>::getInstance();

// Controllers
EventBus *eventBus = &EventBus::getInstance();
DrivetrainController drivetrainController(eventBus);
BallCollectorController ballCollectorController(eventBus);

void setup_input()
{
    // Setup input
    inputMapper.initialize(eventBus);
    inputMapper.setEventMapper([](InputType type, const InputData &data) -> Event
                               {
        Event event;
        switch (type) {
            case InputType::GAMEPAD:
                event.type = EventType::GAMEPAD_EVENT;
                event.data = const_cast<GamepadData *>(&data.gamepadData);
                break;
            case InputType::COLOR_SENSOR:
                event.type = EventType::COLOR_SENSOR_EVENT;
                event.data = const_cast<ColorSensorData *>(&data.colorSensorData);
                break;
            // Handle other input types
        }
        return event; });

    std::unique_ptr<Gamepad> gamepad(new Gamepad());
    std::unique_ptr<ColorSensor> colorSensor(new ColorSensor());
    std::unique_ptr<LimitSwitch> limitSwitch(new LimitSwitch(LIMIT_SWITCH_PIN));

    inputMapper.addInputDevice(gamepad.get());
    inputMapper.addInputDevice(colorSensor.get());
    inputMapper.addInputDevice(limitSwitch.get());
}

void setup()
{
    setup_input();
    // Initialize controllers
    drivetrainController.initialize();
    ballCollectorController.initialize();

    // Start controller tasks
    drivetrainController.start();
    ballCollectorController.start();

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();
}

void loop()
{
    // Main loop can be empty or handle any system-wide tasks
    
    // Just for example
    // poll input devices every 1 second
    while (true)
    {
        inputMapper.update(InputType::GAMEPAD);
        inputMapper.update(InputType::COLOR_SENSOR);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}