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
    data.rpm = getRpm();
    if(data.updateParams){
        setEncARes((float)data.encRes);
    }
}
inline float getRpm() {
    static float lastPos = 0.0f;
    static uint32_t lastTimeUs = 0;

    uint32_t nowUs = micros();
    float curPos = encA.getPos();   // turns

    uint32_t dtUs = nowUs - lastTimeUs;
    if (dtUs < 10000) {             // <10ms → too noisy
        return 0.0f;
    }

    float dTurns = curPos - lastPos;

    lastPos = curPos;
    lastTimeUs = nowUs;

    // RPM = turns/sec * 60
    return (dTurns * 60.0f * 1000000.0f) / dtUs;
}
