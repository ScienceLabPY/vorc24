#ifndef SHOOTING_CONTROLLER_HPP
#define SHOOTING_CONTROLLER_HPP

#include "BaseController.hpp"
#include <device/output/HDMotor.hpp>
#include <device/output/Servo/ContinuousRotationServo.hpp>

namespace sl_core
{
    class ShootingController : public BaseController
    {
    public:
        ShootingController(EventBus *eventBus);
        void initialize() override;
        void handleEvent(const Event &event) override;

    private:
        void _run() override;
        HDMotor shootingMotor;
        ContinuousRotationServo angleServo;
    };
}

#endif // SHOOTING_CONTROLLER_HPP