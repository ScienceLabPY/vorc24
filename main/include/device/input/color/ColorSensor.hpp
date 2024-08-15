#ifndef COLOR_SENSOR_HPP

#define COLOR_SENSOR_HPP

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include "../IDeviceInput.hpp"
#include "ColorSensorData.hpp"

class ColorSensor : public IDeviceInput
{
private:
    Adafruit_TCS34725 tcs;

public:
    ColorSensor();
    InputType getType() const override;
    InputData read() override;

    bool isWhite(ColorSensorData data);
};

#endif // COLOR_SENSOR_HPP