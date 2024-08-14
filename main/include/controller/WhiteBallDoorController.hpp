#ifndef WHITE_BALL_DOOR_CONTROLLER_HPP
#define WHITE_BALL_DOOR_CONTROLLER_HPP

#include "core/event/IEventListener.hpp"
#include "core/event/EventTypes.hpp"
#include "device/input/gamepad/GamepadData.hpp"

namespace sl_core
{
    class WhiteBallDoorController : public IEventListener<GamepadData>
    {
    public:
        WhiteBallDoorController();
        ~WhiteBallDoorController();

        void onEvent(GamepadData data) override;
    private:
        StandardServo doorServo;
        bool state;
    };
}

#endif // WHITE_BALL_DOOR_CONTROLLER_HPP