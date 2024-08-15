#ifndef BALL_COLLECTOR_CONTROLLER_HPP
#define BALL_COLLECTOR_CONTROLLER_HPP

#include "BaseController.hpp"
#include <device/output/HDMotor.hpp>

namespace sl_core
{

    class BallCollectorController : public BaseController
    {
    public:
        BallCollectorController(EventBus *eventBus);
        void initialize() override;
        void handleEvent(const Event &event) override;

    private:
        void _run() override;
        HDMotor m_intakeMotor;
    };

} // namespace sl_core

#endif // BALL_COLLECTOR_CONTROLLER_HPP