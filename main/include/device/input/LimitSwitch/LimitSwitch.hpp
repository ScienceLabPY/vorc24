#ifndef LIMIT_SWITCH_HPP

#define LIMIT_SWITCH_HPP

#include "../IDeviceInput.hpp"
#include "LimitSwitchData.hpp"

namespace sl_core
{
    class LimitSwitch : public IDeviceInput
    {
    public:
        LimitSwitch(int);
        ~LimitSwitch();

        void update() override;
        InputType getType() override;
        LimitSwitchData getData();
    private:
        int switchPin;
        LimitSwitchData data;
    };
}


#endif