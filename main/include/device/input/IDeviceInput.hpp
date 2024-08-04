#ifndef IDEVICE_INPUT_HPP
#define IDEVICE_INPUT_HPP

#include "InputTypes.hpp"

namespace sl_core
{
    class IDeviceInput
    {
    public:
        IDeviceInput(/* args */) {}
        virtual ~IDeviceInput() {}

        virtual void update() = 0;
        virtual InputType getType() = 0;
    };
}

#endif // IDEVICE_INPUT_HPP