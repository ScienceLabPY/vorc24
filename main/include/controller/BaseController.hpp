// BaseController.hpp
#ifndef BASE_CONTROLLER_HPP
#define BASE_CONTROLLER_HPP

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <core/event/EventBus.hpp>
#include <core/event/EventTypes.hpp>

namespace sl_core
{

    class BaseController
    {
    public:
        BaseController(EventBus *eventBus, const char *taskName, uint32_t stackSize = 4096, UBaseType_t priority = 1);

        virtual ~BaseController();

        void start();

        virtual void initialize() = 0;
        virtual void handleEvent(const Event &event) = 0;

    protected:
        EventBus *eventBus;

    private:
        static void _taskFunction(void *pvParameters);
        virtual void _run() = 0;

        const char *m_taskName;
        uint32_t m_stackSize;
        UBaseType_t m_priority;
        TaskHandle_t m_taskHandle;
    };

} // namespace sl_core

#endif // BASE_CONTROLLER_HPP