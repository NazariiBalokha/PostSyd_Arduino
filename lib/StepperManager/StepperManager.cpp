#include <StepperManager.h>
#include <Arduino.h>


StepperManager::StepperManager(int pin1, int pin2, int pin3, int pin4, int delayTime) 
    : pin1(pin1), pin2(pin2), pin3(pin3), pin4(pin4), delayTime(delayTime) {
    // Attach the pins to the stepper motor
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);
}


void StepperManager::spinMotor(int steps) {
    for (int i = 0; i < steps; i++) {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
        delay(delayTime);
        
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
        delay(delayTime);
        
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);
        delay(delayTime);
        
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);
        delay(delayTime);
    }
}