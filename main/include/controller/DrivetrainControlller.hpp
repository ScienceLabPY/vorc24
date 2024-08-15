#ifndef DRIVE_TRAIN_CONTROLLER_HPP
#define DRIVE_TRAIN_CONTROLLER_HPP

#include "BaseController.hpp"
#include "core/event/EventTypes.hpp"
#include "device/input/gamepad/GamepadData.hpp"
#include "device/output/HDMotor.hpp"

namespace sl_core
{
    class DrivetrainController : public BaseController
    {
    public:
        DrivetrainController(EventBus *eventBus);
        void initialize() override;
        void handleEvent(const Event &event) override;

    private:
        // implement motor control here
        HDMotor *leftMotor;
        HDMotor *rightMotor;
        
        const double minJoystick = -1.0;
        const double maxJoystick = 1.0;
        const double minSpeed = -1.0;
        const double maxSpeed = 1.0;

        void _run() override;
    };
}

#endif // DRIVE_TRAIN_CONTROLLER_HPP