#include "initIO.h"


void initIO(){
    pinMode(PINS::SYNC_LED, OUTPUT);
    initEnc();
    initSpindle();
    initStepper();
}

void pin(int pin, bool state){
    digitalWrite(pin, state ? HIGH : LOW);
}

void pin(int pin){
    digitalRead(pin);
}

void apin(int pin, int val){
    analogWrite(pin, val);
}

void apin(int pin){
    analogRead(pin);
}


void runTasks(){
    encTask();
    spindleTask();
    stepperTask();
}


void clearControl(){
    
}
