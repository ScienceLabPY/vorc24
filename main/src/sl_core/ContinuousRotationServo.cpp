#include "include/device/output/RCServo/ContinuousRotationServo.hpp"
using namespace sl_core;

#define SERVO_MIN  150
#define SERVO_MAX  600
#define SERVO_STOP 375
#define SERVO_FREQ 50

ContinuousRotationServo::ContinuousRotationServo(int pwmPin) {
    pinMode(pwmPin,OUTPUT);
    this->pwmPin = pwmPin;
}

ContinuousRotationServo::~ContinuousRotationServo {
    stop();
    ledcDetachPin(this->pwmPin);
}

void ContinuousRotationServo::setSpeed(float Speed) {
    speed = constrain(speed, -1.0, 1.0);
    int value = map(speed*1000,-1000, 1000, SERVO_MIN, SERVO_MAX);
    pwm.setPWM(this->pwmPin,0,value);
}
