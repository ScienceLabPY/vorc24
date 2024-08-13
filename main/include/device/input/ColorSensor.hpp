#ifndef COLOR_SENSOR_HPP

#define COLOR_SENSOR_HPP

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>

class ColorSensor {
    private:
        Adafruit_TCS34725 tcs;
        int R,G,B,C;
    public:
        ColorSensor();
        ~ColorSensor();

        void update();
        bool isWhite();
}

#endif //COLOR_SENSOR_HPP