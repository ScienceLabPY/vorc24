#ifndef I_DEVICE_INPUT_HPP
#define I_DEVICE_INPUT_HPP

#include "InputTypes.hpp"

namespace sl_core
{
    class IDeviceInput
    {
    public:
        virtual ~IDeviceInput() = default;
        virtual InputType getType() const = 0;
        virtual InputData read() = 0;
    };

} // namespace sl_core

#endif // I_DEVICE_INPUT_HPP