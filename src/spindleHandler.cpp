#include "spindleHandler.h"

bool brakeState = true, tmUpdate = false, spdlDir = false;
uint32_t oldTm;
uint8_t oldspd;

void initSpindle(){
    pinMode(PINS::SPDL_PWM, OUTPUT);
    pinMode(PINS::SPDL_DIR, OUTPUT);
    pinMode(PINS::SPDL_BRK, OUTPUT);
}

void setSpindleSpeed(uint8_t speed){
    if(oldspd != speed){
        oldspd = speed;
        apin(PINS::SPDL_PWM, speed);
    }
}

void setSpindleDirection(bool dir){
    if(dir != spdlDir){
        spdlDir = dir;
        pin(PINS::SPDL_DIR, dir);
    }
}


void applyBrake(){
    brakeState = true;
    pin(PINS::SPDL_BRK, true);
}

bool stopBrake() {
    pin(PINS::SPDL_BRK, false);
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



