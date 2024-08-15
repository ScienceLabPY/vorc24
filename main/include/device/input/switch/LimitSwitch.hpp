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

        InputType getType() const override;
        InputData read() override;
    private:
        int switchPin;
    };
}


#endif