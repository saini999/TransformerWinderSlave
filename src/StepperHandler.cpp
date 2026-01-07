#include "StepperHandler.h"

AccelStepper stepper(AccelStepper::DRIVER, PINS::STEP_PULSE_PIN, PINS::STEP_DIR_PIN); // Stepper Object

uint32_t stepPerMM;

float oldSetPos = 0;
int32_t oldCurPos = 0;
bool isInverted = false;

void initStepper(){
    pinMode(PINS::STEP_PULSE_PIN, OUTPUT);
    pinMode(PINS::STEP_DIR_PIN, OUTPUT);
    stepper.setCurrentPosition(0);
    stepper.setMaxSpeed(10000.0f);
    stepper.setSpeed(5000.0f);
    stepper.setAcceleration(5000.0f);
      
}

void CalculateStepsPerMM(){
    stepPerMM = (uint32_t)((data.stepRes * data.gearRatio) / data.screwPitch);
}

inline int32_t getSetPos () {
    return (int32_t) (data.setYPos * stepPerMM);
}

inline float getCurPos (int32_t curPos) {
    return (float) (curPos / (float) stepPerMM);
}


void stepperTask(){
    if(data.InvertStepDir && !isInverted){
        stepper.setPinsInverted(true);
        isInverted = true;
    } else if(!data.InvertStepDir && isInverted){
        stepper.setPinsInverted();
        isInverted = false;
    }
    if(data.moveStep){
        if(fabs(oldSetPos - data.setYPos) > 0.001f){
            stepper.moveTo(getSetPos());
            oldSetPos = data.setYPos;
        }
        int32_t curPos = stepper.currentPosition();
        if(oldCurPos != curPos){
            data.curYPos = getCurPos(curPos);
            oldCurPos = curPos;
            if(curPos != 0 && !data.atZero){data.atZero = true;}
        }
        stepper.run();
    }
    if(stepper.distanceToGo() == 0){
        data.stepDone = true;
    } else { data.stepDone = false; }
    if(data.zeroStep){
        data.setYPos = 0;
        data.curYPos = 0;
        stepper.setCurrentPosition(0);
        stepper.moveTo(0);
        oldSetPos = 0;
        oldCurPos = 0;
    }
    if(data.updateParams){
        CalculateStepsPerMM();
    }
}
