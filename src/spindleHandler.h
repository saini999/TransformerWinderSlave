#ifndef SPENDLEHANDLER_H
#define SPENDLEHANDLER_H    

#include <Arduino.h>
#include "initIO.h"
#include "RegDef.h"

extern bool brakeState, tmUpdate, spdlDir;
extern uint32_t oldTm;
extern uint8_t oldspd;
void initSpindle();

void setSpindleSpeed(uint8_t speed);

void setSpindleDirection(bool dir);


void applyBrake();

bool stopBrake();

void spindleTask();

#endif