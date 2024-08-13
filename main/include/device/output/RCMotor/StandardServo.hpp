#ifndef STANDARD_SERVO_HPP

#define STANDARD_SERVO_HPP

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