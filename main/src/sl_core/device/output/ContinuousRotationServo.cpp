#include <device/output/ContinuousRotationServo.hpp>
using namespace sl_core;

#define SERVO_MIN  150
#define SERVO_MAX  600
#define SERVO_STOP 375
#define SERVO_FREQ 50

ContinuousRotationServo::ContinuousRotationServo(int pwmPin) {
    pinMode(pwmPin,OUTPUT);
    this->pwmPin = pwmPin;
    pwmCRS.setPWMFreq(SERVO_FREQ);
}

ContinuousRotationServo::~ContinuousRotationServo {
    stop();
    ledcDetachPin(this->pwmPin);
}

void ContinuousRotationServo::setSpeed(float Speed) {
    speed = constrain(speed, -1.0, 1.0);
    // Map the speed to the PWM value
    int value = map(speed*1000, -1000, 1000, SERVO_MIN, SERVO_MAX);
    pwmCRS.setPWM(this->pwmPin,0,value);
}
