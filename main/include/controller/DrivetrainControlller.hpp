#ifndef DRIVE_TRAIN_CONTROLLER_HPP
#define DRIVE_TRAIN_CONTROLLER_HPP

#include "core/event/IEventListener.hpp"
#include "core/event/EventTypes.hpp"
#include "device/input/gamepad/GamepadData.hpp"

namespace sl_core
{
    class DrivetrainController : public IEventListener<GamepadData>
    {
    public:
        DrivetrainController();
        ~DrivetrainController();

        void onEvent(GamepadData data) override;
    private:
        // implement motor control here
        HDMotor leftMotor;
        HDMotor rightMotor;
        // Motor* leftMotor;
        // Motor* rightMotor;
    };
}

#endif // DRIVE_TRAIN_CONTROLLER_HPP