#ifndef STEPPER_HANDLER_H

#define STEPPER_HANDLER_H
#include <Arduino.h>
#include "initIO.h"
#include "RegDef.h"
#include <AccelStepper.h>

extern AccelStepper stepper; // Stepper Object

extern uint32_t stepPerMM;

extern float oldSetPos;
extern int32_t oldCurPos;
extern bool isInverted;

void initStepper();
void CalculateStepsPerMM();

inline int32_t getSetPos();

inline float getCurPos (int32_t curPos);


void stepperTask();

#endif