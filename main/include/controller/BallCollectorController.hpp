#ifndef BALL_COLLECTOR_CONTROLLER_HPP
#define BALL_COLLECTOR_CONTROLLER_HPP

#include "core/event/IEventListener.hpp"
#include "core/event/EventTypes.hpp"
#include "device/input/gamepad/GamepadData.hpp"

namespace sl_core
{
    class BallCollectorController : public IEventListener<GamepadData>
    {
    public:
        BallCollectorController();
        ~BallCollectorController();

        void onEvent(GamepadData data) override;
    private:
        HDMotor intakeMotor;
    };
}

#endif // BALL_COLLECTOR_CONTROLLER_HPP