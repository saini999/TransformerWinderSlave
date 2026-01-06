#ifndef REG_DEF_H

#define REG_DEF_H
#include <Arduino.h>

enum RegNum {
    CONTROL = 0,
    FEEDBACK = 1,
    SET_TURNS = 2,
    CUR_TURNS = 4,
    SET_YPOS = 6,
    CUR_YPOS = 8,
    RPM = 10,
    SPEED = 12,
    POWER = 13,
    ENC_RES = 14,
    STEP_RES = 15,
    SCREW_PITCH = 16,
    GEAR_RATIO = 18,
};

enum ControlReg {
    SYNC = 0,
    MOVESTEP = 1,
    ZEROSTEP = 2,
    RESETENC = 3,
    DIR_MOTOR = 4,
    RUN_MOTOR = 5,
    UPDATE_PARAMS = 6,
    RUN_REF = 7,
    INVERT_STEP = 8,
};

enum FeedbackReg {
    STEP_DONE = 0,
    AT_ZERO = 1,
    ENC_AT_ZERO = 2,
    MOTOR_RUNNING = 3,
    PARAMS_SAVED = 4,
    REF_DONE = 5,
};

struct dataRegister{
    bool sync;
    bool moveStep;
    bool zeroStep;
    bool resetEnc;
    bool dirMotor;
    bool runMotor;
    bool updateParams;
    bool runRef;
    bool InvertStepDir;
    bool stepDone;
    bool atZero;
    bool encAtZero;
    bool motorRunning;
    bool paramsSaved;
    bool refDone;
    uint16_t setTurns;
    float curTurns;
    float setYPos;
    float curYPos;
    float rpm;
    uint8_t speed;
    uint8_t power;
    uint16_t encRes;
    float stepRes;
    float screwPitch;
    float gearRatio;
};

extern dataRegister data;

#endif