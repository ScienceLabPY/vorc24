#include <device/input/ColorSensor.hpp>
using namespace sl_core;

#define WHITE_LIMIT 1534

ColorSensor::ColorSensor(){
    this->tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
};

ColorSensor::~ColorSenSor() {

};

void ColorSensor::update() {
    uint16_t r, g, b, c;
    this->tcs.getRawData(&r, &g, &b, &c);
    this->R = r;
    this->G = g;
    this->B = b;
    this->C = c;
}

bool ColorSensor::isWhite() {
    this.update();
    return this->R + this->G + this->B >= WHITE_LIMIT;
    // READ THE EXPLANATION IN THE PROGRAMMING DOCUMENT.
}