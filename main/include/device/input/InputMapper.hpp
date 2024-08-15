#ifndef INPUT_CONTROLLER_HPP
#define INPUT_CONTROLLER_HPP

#include <map>
#include <functional>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include "InputTypes.hpp"
#include "IDeviceInput.hpp"
#include <core/event/EventBus.hpp>

namespace sl_core
{
    template<typename EventType>
    class InputMapper
    {
    public:
        static InputMapper& getInstance();

        void update(InputType type);
        // polling mode
        void addInputDevice(IDeviceInput* inputDevice);
        // interrupt mode
        void addInputDevice(IDeviceInput* inputDevice, gpio_num_t interruptPin);
        void removeInputDevice(IDeviceInput* inputDevice);
        void initialize(EventBus* eventBus);
        void setEventMapper(std::function<EventType(InputType, const InputData&)> mapper);

    private:
        InputMapper();
        ~InputMapper();
        InputMapper(const InputMapper&) = delete;
        InputMapper& operator=(const InputMapper&) = delete;

        static void IRAM_ATTR gpioIsrHandler(void* arg);
        static void inputProcessingTask(void* pvParameters);

        std::map<InputType, IDeviceInput*> inputDevices;
        std::map<gpio_num_t, InputType> interruptPins;
        SemaphoreHandle_t mutex;
        QueueHandle_t inputQueue;
        TaskHandle_t processingTaskHandle;
        EventBus* eventBus;
        std::function<EventType(InputType, const InputData&)> eventMapper;
    };
}

#endif // INPUT_CONTROLLER_HPP