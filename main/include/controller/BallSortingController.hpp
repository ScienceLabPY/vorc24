#ifndef BALL_SORTING_CONTROLLER_HPP
#define BALL_SORTING_CONTROLLER_HPP


#include <BaseController.hpp>
#include <device/output/RCMotor/ContinuousRotationServo.hpp>
#include <device/input/switch/LimitSwitch.hpp>

namespace sl_core
{
    class BallSortingController : public BaseController
    {
    public:
        BallSortingController();
        void initialize() override;
        void handleEvent(Event *event) override;
    private:
        void _run() override;

        const TIME_TO_SET_ANGLE = 500;
        ColorSensor colorSensor;
        ContinuousRotationServo sortingServo;
    };
}

#endif // BALL_SORTING_CONTROLLER_HPP