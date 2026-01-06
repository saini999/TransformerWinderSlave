#include "spindleHandler.h"
void initSpindle(){
    pinMode(PINS::SPDL_PWM, OUTPUT);
    pinMode(PINS::SPDL_DIR, OUTPUT);
    pinMode(PINS::SPDL_BRK, OUTPUT);
}

void setSpindleSpeed(uint8_t speed){
    analogWrite(PINS::SPDL_PWM, speed);
}

void setSpindleDirection(bool dir){
    digitalWrite(PINS::SPDL_DIR, dir ? HIGH : LOW);
}

bool brakeState = true, tmUpdate = false;
uint32_t oldTm;
void applyBrake(){
    brakeState = true;
    digitalWrite(PINS::SPDL_BRK, HIGH);
}

bool stopBrake() {
    digitalWrite(PINS::SPDL_BRK, LOW);
    if(!tmUpdate) {
        oldTm = millis();
        tmUpdate = true;
    }
    if(brakeState && (millis() - oldTm > 200)) {
        brakeState = false;
        oldTm = millis();
        return false;
    } else {
        return true;
    }
    return false;
}

void spindleTask(){
    if(data.runMotor){
        if(stopBrake()){
            setSpindleDirection(data.dirMotor);
            setSpindleSpeed(data.speed);
            data.motorRunning = true;
        }
    } else {
        setSpindleSpeed(0);
        applyBrake();
        data.motorRunning = false;
        tmUpdate = false;
    }
}



