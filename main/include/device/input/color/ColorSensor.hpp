#ifndef COLOR_SENSOR_HPP

#define COLOR_SENSOR_HPP

#include <Arduino.h>
#include <Wire.h>
#include "ColorSensorData.hpp"
#include <Adafruit_TCS34725.h>

class ColorSensor
{
private:
    Adafruit_TCS34725 tcs;

public:
    ColorSensor();
    InputType getType() const override;
    InputData read() override;

    bool isWhite();
}

#endif // COLOR_SENSOR_HPP