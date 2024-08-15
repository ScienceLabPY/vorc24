#include <device/input/color/ColorSensor.hpp>

using namespace sl_core;

#define WHITE_LIMIT 1534

ColorSensor::ColorSensor(){
    this->tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
};

InputType ColorSensor::getType() const {
    return InputType::COLOR_SENSOR;
}

InputData ColorSensor::read() {
    uint16_t r, g, b, c;
    this->tcs.getRawData(&r, &g, &b, &c);
    InputData data;
    data.colorSensorData.R = r;
    data.colorSensorData.G = g;
    data.colorSensorData.B = b;
    data.colorSensorData.C = c;
    return data;
}

bool ColorSensor::isWhite(ColorSensorData data) {
    return (data.R + data.G + data.B) > WHITE_LIMIT;
    // READ THE EXPLANATION IN THE PROGRAMMING DOCUMENT.
}