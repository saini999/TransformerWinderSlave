#include "encHandler.h"

Encoder encA(PINS::ENCA_A, PINS::ENCA_B);

inline void encUpdate(){
    encA.update();
}

void initEnc(){
    pinMode(PINS::ENCA_A, INPUT);
    pinMode(PINS::ENCA_B, INPUT);
    encA.setResolution(1.0f);
    attachInterrupt(digitalPinToInterrupt(PINS::ENCA_A), encUpdate, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PINS::ENCA_B), encUpdate, CHANGE);
}

inline float getEncAPos(){
    return encA.getPos();
}

inline void resetEncA(){
    encA.write(0);
}

inline void setEncARes(float res){
    encA.setResolution(res);
}

void encTask(){
    if(data.resetEnc){
        resetEncA();
        data.encAtZero = true;
        data.resetEnc = false;
    }
    data.curTurns = getEncAPos();
    if(data.updateParams){
        setEncARes((float)data.encRes);
    }
}
