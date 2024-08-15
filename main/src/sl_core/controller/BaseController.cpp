#include <controller/BaseController.hpp>

using namespace sl_core;

BaseController::BaseController(
    EventBus *eventBus, 
    const char *taskName, 
    uint32_t stackSize, 
    UBaseType_t priority) : 
        eventBus(eventBus),
        m_taskHandle(nullptr),
        m_taskName(taskName), 
        m_stackSize(stackSize), 
        m_priority(priority)
{
}

BaseController::~BaseController()

{
    if (m_taskHandle != nullptr)
    {
        vTaskDelete(m_taskHandle);
    }
}

void BaseController::start()
{
    xTaskCreate(_taskFunction, m_taskName, m_stackSize, this, m_priority, &m_taskHandle);
}

void BaseController::_taskFunction(void *pvParameters)
{
    BaseController *controller = static_cast<BaseController *>(pvParameters);
    controller->_run();
}