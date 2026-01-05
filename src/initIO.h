#ifndef INITIO_H
#define INITIO_H
#include <Arduino.h>


void initIO(){
    pinMode(LED_BUILTIN, OUTPUT);
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

#endif