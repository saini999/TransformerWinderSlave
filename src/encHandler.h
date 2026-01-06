#ifndef ENCHANDLER_H
#define ENCHANDLER_H

#include <Arduino.h>

#include "initIO.h"
#include "RegDef.h"
#include "Encoder.h"

inline void encUpdate();
inline float getRpm();

void initEnc();

inline float getEncAPos();

inline void resetEncA();

inline void setEncARes(float res);

void encTask();

#endif