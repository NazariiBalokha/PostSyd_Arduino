#ifndef SERVO_MANAGER_H
#define SERVO_MANAGER_H

#include <Servo.h>
#include <Arduino.h>
#include "StepperManager.h"

class ServoManager
{
    public:
        ServoManager(bool reversed = false);

        void attach(int pin);
        void manualControl(int angle);
        void openGate();
        void closeGate();
        void testServo();
    
    private:
        Servo servo;
        StepperManager* stepper;
        bool reversed;
};
#endif // SERVO_MANAGER_H