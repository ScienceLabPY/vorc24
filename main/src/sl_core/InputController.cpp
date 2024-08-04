#include <algorithm>
#include <controller/InputController.hpp>
using namespace sl_core;

InputController::InputController()
{
}

InputController::~InputController()
{
}

// This function is called by the system (interrupt/polling/dma) to update the input devices
void InputController::update(InputType type)
{
    inputDevices[type]->update();
}

void InputController::addInputDevice(IDeviceInput* inputDevice)
{
    inputDevices[inputDevice->getType()] = inputDevice;
}

void InputController::removeInputDevice(IDeviceInput* inputDevice)
{
    inputDevices.erase(inputDevice->getType());
}