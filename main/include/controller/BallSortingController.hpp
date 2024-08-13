#ifndef BALL_SORTING_CONTROLLER_HPP
#define BALL_SORTING_CONTROLLER_HPP

#include "core/event/IEventListener.hpp"
#include "core/event/EventTypes.hpp"
#include "device/input/LimitSwitch/LimitSwitchData.hpp"

namespace sl_core
{
    class BallSortingController : public IEventListener<LimitSwitchData>
    {
    public:
        BallSortingController();
        ~BallSortingController();

        void onEvent(LimitSwitchData data) override;
    private:
        ColorSensor colorSensor;
        ContinuousRotationServo sortingServo;
    };
}

#endif // BALL_SORTING_CONTROLLER_HPP