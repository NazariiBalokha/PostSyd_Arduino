#ifndef STEPPER_MANAAGER_H
#define STEPPER_MANAAGER_H

#include <Arduino.h>

class StepperManager
{
    public:
        StepperManager(int pin1, int pin2, int pin3, int pin4, int delayTime);

        void spinMotor(int steps);
    
    private:
        int pin1;
        int pin2;
        int pin3;
        int pin4;
        int delayTime;

};
#endif // STEPPER_MANAAGER_H