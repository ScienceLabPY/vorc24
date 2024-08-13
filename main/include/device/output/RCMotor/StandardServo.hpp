#ifndef STANDARD_SERVO_HPP

#define STANDARD_SERVO_HPP

#include <Arduino>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

namespace sl_core {
    class StandardServo {
        private: 
            int pwmPin;
        public:
            StandardServo(int);
            ~StandardServo();
            
            void setAngle(int);
    }
}

#endif //STANDARD_SERVO_HPP