#include <device/HDMotor.hpp>
using namespace sl_core;

HDMotor::HDMotor(int pwmPin, int dirPin, int encA, int encB, int channel, bool reversed)
    : pwmPin(pwmPin), dirPin(dirPin), encoderPinA(encA), encoderPinB(encB), isReversed(reversed), encoderCount(0), lastEncoded(0), ledChannel(channel)
{
    // Set up motor pins
    pinMode(pwmPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(encoderPinA, INPUT_PULLUP);
    pinMode(encoderPinB, INPUT_PULLUP);

    // Set up LEDC (PWM) for motor speed control
    ledcSetup(ledChannel, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(pwmPin, ledChannel);
}

HDMotor::~HDMotor()
{
    // Stop the motor and detach the LEDC channel
    stop();
    ledcDetachPin(pwmPin);
    
    // Reset encoder pins
    pinMode(encoderPinA, INPUT);
    pinMode(encoderPinB, INPUT);

    // Detach interrupts
    detachInterrupt(encoderPinA);
    detachInterrupt(encoderPinB);

    // Reset encoder count
    resetEncoder();
}

void HDMotor::setSpeed(float speed)
{
    speed = constrain(speed, -1.0, 1.0);

    if (isReversed)
    {
        speed = -speed;
    }

    digitalWrite(dirPin, speed > 0 ? HIGH : LOW);

    int pwmValue = map(abs(speed) * 1000, 0, 1000, 0, 255);
    ledcWrite(ledChannel, pwmValue);
}

void HDMotor::stop()
{
    setSpeed(0);
}

long HDMotor::getEncoderCount()
{
    return encoderCount;
}

void HDMotor::resetEncoder()
{
    encoderCount = 0;
}

void HDMotor::updateEncoder()
{
    int MSB = digitalRead(encoderPinA);
    int LSB = digitalRead(encoderPinB);

    int encoded = (MSB << 1) | LSB;
    // Calculate the sum of the previous encoded value and the current encoded value
    int sum = (lastEncoded << 2) | encoded;

    // Check the sum value to determine the direction of rotation and update the encoder count accordingly
    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
        encoderCount++;
    if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
        encoderCount--;

    lastEncoded = encoded;
}