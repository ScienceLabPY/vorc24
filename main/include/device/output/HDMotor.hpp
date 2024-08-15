#ifndef HDMOTOR_HPP
#define HDMOTOR_HPP

#include <Arduino.h>

#define ENCODER_COUNTS_PER_REV 1440
#define PWM_MAX 4095
#define PWM_MIN 0

namespace sl_core
{
    class HDMotor
    {
    private:
        int pwmPin;
        int dirPin;
        int encoderPinA;
        int encoderPinB;
        bool isReversed;
        volatile long encoderCount;
        int lastEncoded;

        // LEDC (PWM) parameters
        int ledChannel;
        static const int PWM_FREQ = 5000;     // 5 kHz PWM frequency
        static const int PWM_RESOLUTION = 12; // 12-bit resolution, 4096 possible values

    public:
        HDMotor(int pwmPin, int dirPin, int encA, int encB, int channel, bool reversed = false);
        ~HDMotor();

        void setSpeed(float speed);

        void stop();
        long getEncoderCount();

        void resetEncoder();
        void updateEncoder();

        int getEncoderPinA() { return encoderPinA; }
        int getEncoderPinB() { return encoderPinB; }
    };
} // namespace sl_core

#endif // HDMOTOR_HPP