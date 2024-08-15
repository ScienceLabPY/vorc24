// InputMapper.cpp
#include <algorithm>
#include "device/input/InputMapper.hpp"

using namespace sl_core;

#define INPUT_QUEUE_SIZE 10
#define INPUT_TASK_STACK_SIZE 2048
#define INPUT_TASK_PRIORITY 2

template <typename EventType>
InputMapper<EventType>::InputMapper() : eventBus(nullptr), eventMapper(nullptr)
{
    mutex = xSemaphoreCreateMutex();
    inputQueue = xQueueCreate(INPUT_QUEUE_SIZE, sizeof(InputEvent<EventType>));
}

template <typename EventType>
InputMapper<EventType>::~InputMapper()
{
    vSemaphoreDelete(mutex);
    vQueueDelete(inputQueue);
    if (processingTaskHandle != nullptr)
    {
        vTaskDelete(processingTaskHandle);
    }
}

template <typename EventType>
InputMapper<EventType> &InputMapper<EventType>::getInstance()
{
    static InputMapper<EventType> instance;
    return instance;
}

template <typename EventType>
void InputMapper<EventType>::initialize(EventBus *eb)
{
    eventBus = eb;
    xTaskCreate(inputProcessingTask, "InputProcessor", INPUT_TASK_STACK_SIZE, this, INPUT_TASK_PRIORITY, &processingTaskHandle);
}

template <typename EventType>
void InputMapper<EventType>::setEventMapper(std::function<EventType(InputType, const InputData &)> mapper)
{
    eventMapper = mapper;
}

template <typename EventType>
void InputMapper<EventType>::update(InputType type)
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    auto it = inputDevices.find(type);
    if (it != inputDevices.end())
    {
        InputEvent<EventType> event;
        event.type = type;
        event.data = it->second->read();
        xQueueSend(inputQueue, &event, 0);
    }
    xSemaphoreGive(mutex);
}

template <typename EventType>
void InputMapper<EventType>::addInputDevice(IDeviceInput *inputDevice)
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    inputDevices[inputDevice->getType()] = inputDevice;
    xSemaphoreGive(mutex);
}

template <typename EventType>
void InputMapper<EventType>::addInputDevice(IDeviceInput *inputDevice, gpio_num_t interruptPin)
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    inputDevices[inputDevice->getType()] = inputDevice;
    interruptPins[interruptPin] = inputDevice->getType();

    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_ANYEDGE;
    io_conf.pin_bit_mask = (1ULL << interruptPin);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(interruptPin, gpioIsrHandler, this);

    xSemaphoreGive(mutex);
}

template <typename EventType>
void InputMapper<EventType>::removeInputDevice(IDeviceInput *inputDevice)
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    InputType type = inputDevice->getType();
    inputDevices.erase(type);

    // if the input device is interrupt-based, remove the interrupt handler
    for (auto it = interruptPins.begin(); it != interruptPins.end(); ++it)
    {
        if (it->second != type) continue;
        gpio_isr_handler_remove(it->first);
        interruptPins.erase(it);
        break;
    }
    xSemaphoreGive(mutex);
}

template <typename EventType>
void IRAM_ATTR InputMapper<EventType>::gpioIsrHandler(void* arg) {
    InputMapper* mapper = static_cast<InputMapper*>(arg);
    InputEvent event;
    event.type = mapper->interruptPins[gpio_get_level()];
    event.data = mapper->inputDevices[event.type]->read();
    xQueueSendFromISR(mapper->inputQueue, &event, NULL);
}

template <typename EventType>
void InputMapper<EventType>::inputProcessingTask(void *pvParameters)
{
    InputMapper<EventType> *mapper = static_cast<InputMapper*>(pvParameters);
    InputEvent<EventType> event;

    for (;;)
    {
        if (xQueueReceive(mapper->inputQueue, &event, portMAX_DELAY) != pdTRUE)
            continue;
        if (!mapper->eventMapper)
            continue;
        EventType mappedEvent = mapper->eventMapper(event.type, event.data);
        mapper->eventBus->publish(mappedEvent);
    }
}