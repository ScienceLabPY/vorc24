#ifndef WHITE_BALL_DOOR_CONTROLLER_HPP
#define WHITE_BALL_DOOR_CONTROLLER_HPP

#include "Basecontroller.hpp"
#include "device/output/RCMotor/StandardServo.hpp"

namespace sl_core
{
    class WhiteBallDoorController : public BaseController
    {
    public:
        WhiteBallDoorController(EventBus *eventBus);
        void initialize() override;
        void handleEvent(Event *event) override;
    private:
        void _run() override;
        StandardServo doorServo;
    };
}

#endif // WHITE_BALL_DOOR_CONTROLLER_HPP