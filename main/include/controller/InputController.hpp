#ifndef INPUT_CONTROLLER_HPP
#define INPUT_CONTROLLER_HPP

#include <map>
#include "device/input/InputTypes.hpp"
#include "device/input/IDeviceInput.hpp"

namespace sl_core
{
    class InputController
    {
    public:
        InputController();
        ~InputController();
        
        void update(InputType type);
        void addInputDevice(IDeviceInput* inputDevice);
        void removeInputDevice(IDeviceInput* inputDevice);
    private:
        std::map<InputType, IDeviceInput*> inputDevices;
    };
}

#endif // INPUT_CONTROLLER_HPP