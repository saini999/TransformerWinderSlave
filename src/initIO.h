#ifndef INITIO_H
#define INITIO_H
#include <Arduino.h>
#include "EncHandler.h"
#include "spindleHandler.h"
#include "StepperHandler.h"

enum PINS {
    SYNC_LED = LED_BUILTIN,
    ENCA_A = PA0, //TIM2_CH1 ENCODER INPUT A
    ENCA_B = PA1, //TIM2_CH2 ENCODER INPUT B
    SPDL_PWM = PB6, //TIM4_CH1 SPINDLE PWM OUTPUT
    SPDL_DIR = PA8,  //SPINDLE DIRECTION OUTPUT
    SPDL_BRK = PA11,    //SPINDLE BRAKE OUTPUT
    STEP_PULSE_PIN = PA10, //STEPPER PULSE OUTPUT
    STEP_DIR_PIN = PA9    //STEPPER DIRECTION OUTPUT
};

void initIO();

void pin(int pin, bool state);

void pin(int pin);

void apin(int pin, int val);

void apin(int pin);


void runTasks();


void clearControl();

#endif