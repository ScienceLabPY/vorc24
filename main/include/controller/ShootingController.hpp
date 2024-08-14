#ifndef SHOOTING_CONTROLLER_HPP
#define SHOOTING_CONTROLLER_HPP

#include "core/event/IEventListener.hpp"
#include "core/event/EventTypes.hpp"
#include "device/input/gamepad/GamepadData.hpp"

namespace sl_core
{
    class ShootingController : public IEventListener<GamepadData>
    {
    public:
        ShootingController();
        ~ShootingController();

        void onEvent(GamepadData data) override;
    private:
        HDMotor shootingMotor;
        ContinuousRotationServo angleServo;
    };
}

#endif // SHOOTING_CONTROLLER_HPP