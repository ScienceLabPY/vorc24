#include <Arduino.h>
#include <memory>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <core/event/EventBus.hpp>
#include <device/input/InputMapper.hpp>
#include <controller/DrivetrainControlller.hpp>
#include <controller/BallCollectorController.hpp>
#include <controller/BallSortingController.hpp>
#include <controller/ShootingController.hpp>
#include <controller/WhiteBallDoorController.hpp>

#include <device/input/gamepad/Gamepad.hpp>
#include <device/input/color/ColorSensor.hpp>
#include <device/input/switch/LimitSwitch.hpp>

using namespace sl_core;
// Controllers
EventBus *eventBus = &EventBus::getInstance();
DrivetrainController drivetrainController(eventBus);
BallCollectorController ballCollectorController(eventBus);
BallSortingController ballSortingController(eventBus);
ShootingController shootingController(eventBus);
WhiteBallDoorController whiteBallDoorController(eventBus);

void setup_input()
{
    // Setup input
    auto &inputMapper = InputMapper<Event>::getInstance();
    inputMapper.initialize(eventBus);
    inputMapper.setEventMapper([](InputType type, const InputData &data) -> Event
                               {
        Event event;
        event.data = static_cast<void*>(const_cast<InputData*>(&data));
        switch (type) {
            case InputType::GAMEPAD:
                event.type = EventType::GAMEPAD_EVENT;
                break;
            case InputType::COLOR_SENSOR:
                event.type = EventType::COLOR_SENSOR_EVENT;
                break;
            // Handle other input types
        }
        return event; });

    auto gamepad = std::make_unique<Gamepad>();
    auto colorSensor = std::make_unique<ColorSensor>();
    auto limitSwitch = std::make_unique<LimitSwitch>();

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
    ballSortingController.initialize();
    shootingController.initialize();
    whiteBallDoorController.initialize();

    // Start controller tasks
    drivetrainController.start();
    ballCollectorController.start();
    ballSortingController.start();
    shootingController.start();
    whiteBallDoorController.start();

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