#ifndef CONTINUOUS_ROTATION_SERVO

#define CONTINUOUS_ROTATION_SERVO

#include <Arduino>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwmCRS = Adafruit_PWMServoDriver();

namespace sl_core {
    class ContinuousRotationServo {
        private: 
            int pwmPin;
        public:
            ContinuousRotationServo(int);
            ~ContinuousRotationServo();
            
            void setSpeed(float);
    }
}

#endif