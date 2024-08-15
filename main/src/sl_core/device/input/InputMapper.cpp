// InputMapper.cpp
#include <algorithm>
#include "device/input/InputMapper.hpp"

using namespace sl_core;

#define INPUT_QUEUE_SIZE 10
#define INPUT_TASK_STACK_SIZE 2048
#define INPUT_TASK_PRIORITY 2

template<typename EventType>
InputMapper<EventType>::InputMapper() : eventBus(nullptr), eventMapper(nullptr) {
    mutex = xSemaphoreCreateMutex();
    inputQueue = xQueueCreate(INPUT_QUEUE_SIZE, sizeof(InputEvent<EventType>));
}

template<typename EventType>
InputMapper<EventType>::~InputMapper() {
    vSemaphoreDelete(mutex);
    vQueueDelete(inputQueue);
    if (processingTaskHandle != nullptr) {
        vTaskDelete(processingTaskHandle);
    }
}

template<typename EventType>
InputMapper<EventType>& InputMapper<EventType>::getInstance() {
    static InputMapper<EventType> instance;
    return instance;
}

template<typename EventType>
void InputMapper<EventType>::initialize(EventBus* eb) {
    eventBus = eb;
    xTaskCreate(inputProcessingTask, "InputProcessor", INPUT_TASK_STACK_SIZE, this, INPUT_TASK_PRIORITY, &processingTaskHandle);
}

template<typename EventType>
void InputMapper<EventType>::setEventMapper(std::function<EventType(InputType, const InputData&)> mapper) {
    eventMapper = mapper;
}

template<typename EventType>
void InputMapper<EventType>::update(InputType type) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    auto it = inputDevices.find(type);
    if (it != inputDevices.end()) {
        InputEvent<EventType> event;
        event.type = type;
        event.data = it->second->read();
        xQueueSend(inputQueue, &event, 0);
    }
    xSemaphoreGive(mutex);
}

template<typename EventType>
void InputMapper<EventType>::addInputDevice(IDeviceInput* inputDevice) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    inputDevices[inputDevice->getType()] = inputDevice;
    xSemaphoreGive(mutex);
}

template<typename EventType>
void InputMapper<EventType>::removeInputDevice(IDeviceInput* inputDevice) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    inputDevices.erase(inputDevice->getType());
    xSemaphoreGive(mutex);
}

template<typename EventType>
void InputMapper<EventType>::inputProcessingTask(void* pvParameters) {
    InputMapper<EventType>* mapper = static_cast<InputMapper<EventType>*>(pvParameters);
    InputEvent<EventType> event;

    for (;;) {
        if (xQueueReceive(mapper->inputQueue, &event, portMAX_DELAY) != pdTRUE) continue;
        if (!mapper->eventMapper) continue;
        EventType mappedEvent = mapper->eventMapper(event.type, event.data);
        mapper->eventBus->publish(mappedEvent);
    }
}