#include "ServoManager.h"

ServoManager::ServoManager(bool reversed) 
    : reversed(reversed) {}

void ServoManager::attach(int pin) {
    servo.attach(pin);
}

void ServoManager::manualControl(int angle) {
    servo.write(angle);
}

void ServoManager::openGate() {
    if (reversed) {
        servo.write(100); // Open position
    } else {
        servo.write(50); // Open position
    }
}

void ServoManager::closeGate() {
 if (reversed) {
        servo.write(160); // Close position
    } else {
        servo.write(0); // Close position
    }   
}

void ServoManager::testServo() {
    if (reversed) {
        servo.write(160);
    } else {
        servo.write(0);
    }
    delay(500);

    if (reversed) {
        servo.write(20);
    } else {
        servo.write(160);
    }
    
    delay(500);

    if (reversed) {
        servo.write(160);
    } else {
        servo.write(0);
    }

    delay(500);
    openGate();
    delay(500);
    closeGate();
}