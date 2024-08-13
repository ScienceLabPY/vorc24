#include "include/device/output/RCServo/StandarServo.hpp"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
using namespace sl_core;

#define RCSERVO_ANGLE_RANGE 0, 180

#ifndef PWM_RESOLUTION_RANGE
#define PWM_RESOLUTION_RANGE 0, 4095
#endif

StandardServo::StandardServo(int pwmPin) {
    pinMode(pwmPin,OUTPUT);
    this->pwmPin = pwmPin;
}

StandardServo::~StandardServo() {
    stop();
    ledcDetachPin(pwmPin);
}

void StandardServo::setAngle(int angle) {
    int val = map(angle,RCSERVO_ANGLE_RANGE,PWM_RESOLUTION_RANGE);
    pwm.setPWM(this->pwmPin,0,val);
}