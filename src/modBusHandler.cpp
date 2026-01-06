#include "modBusHandler.h"
HardwareSerial Serial3(PB11, PB10);
ModbusSerial mb;

void setupModbus(){
    mb.config(&Serial3, 115200, -1);
    mb.setSlaveId(1);
    
    for (int i = 0; i < NUM_HREG; ++i) 
    {
        mb.addHreg(i);
    }

}

void mbPoll(){
    mb.task();
    updateData();
}

inline bool getBit(uint16_t regIdx, uint8_t bitIdx)
{
    if (bitIdx > 15) return false;
    return (mb.Hreg(regIdx) & (1 << bitIdx)) != 0;
}

inline void setBit(uint16_t regIdx, uint8_t bitIdx, bool value)
{
    if (bitIdx > 15) return;
    uint16_t regValue = mb.Hreg(regIdx);
    if (value)
    {
        regValue |= (1 << bitIdx);
    }
    else
    {
        regValue &= ~(1 << bitIdx);
    }
    mb.Hreg(regIdx, regValue);
}

inline void setFloat(uint16_t regIdx, float value)
{
    union {
        float f;
        uint32_t u;
    } v;

    v.f = value;

    mb.Hreg(regIdx,     (v.u >> 16) & 0xFFFF);
    mb.Hreg(regIdx + 1,  v.u        & 0xFFFF);
}

inline float getFloat(uint16_t regIdx)
{
    union {
        float f;
        uint32_t u;
    } v;

    v.u = ((uint32_t)mb.Hreg(regIdx) << 16) | (uint32_t)mb.Hreg(regIdx + 1);

    return v.f;
}


void updateData()
{
    fetchDataFromRegisters();
    sendDataToRegisters();
}

void fetchDataFromRegisters(){
    data.sync = getBit(RegNum::CONTROL, ControlReg::SYNC);
    data.moveStep = getBit(RegNum::CONTROL, ControlReg::MOVESTEP);
    data.zeroStep = getBit(RegNum::CONTROL, ControlReg::ZEROSTEP);
    data.resetEnc = getBit(RegNum::CONTROL, ControlReg::RESETENC);
    data.dirMotor = getBit(RegNum::CONTROL, ControlReg::DIR_MOTOR);
    data.runMotor = getBit(RegNum::CONTROL, ControlReg::RUN_MOTOR);
    data.updateParams = getBit(RegNum::CONTROL, ControlReg::UPDATE_PARAMS);
    data.runRef = getBit(RegNum::CONTROL, ControlReg::RUN_REF);
    data.InvertStepDir = getBit(RegNum::CONTROL, ControlReg::INVERT_STEP);

    data.setTurns = (int16_t) getFloat(RegNum::SET_TURNS);
    data.setYPos = getFloat(RegNum::SET_YPOS);
    data.speed = (uint8_t) mb.Hreg(RegNum::SPEED);
    data.power = (uint8_t) mb.Hreg(RegNum::POWER);
    data.encRes = mb.Hreg(RegNum::ENC_RES);
    data.stepRes = getFloat(RegNum::STEP_RES);
    data.screwPitch = getFloat(RegNum::SCREW_PITCH);
    data.gearRatio = getFloat(RegNum::GEAR_RATIO);
}

void sendDataToRegisters(){
    setBit(RegNum::FEEDBACK, FeedbackReg::STEP_DONE, data.stepDone);
    setBit(RegNum::FEEDBACK, FeedbackReg::AT_ZERO, data.atZero);
    setBit(RegNum::FEEDBACK, FeedbackReg::ENC_AT_ZERO, data.encAtZero);
    setBit(RegNum::FEEDBACK, FeedbackReg::MOTOR_RUNNING, data.motorRunning);
    setBit(RegNum::FEEDBACK, FeedbackReg::PARAMS_SAVED, data.paramsSaved);
    setBit(RegNum::FEEDBACK, FeedbackReg::REF_DONE, data.refDone);

    setFloat(RegNum::CUR_TURNS, data.curTurns);
    setFloat(RegNum::CUR_YPOS, data.curYPos);
    setFloat(RegNum::RPM, data.rpm);
}
