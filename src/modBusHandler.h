#ifndef MODBUS_HANDLER_H
#define MODBUS_HANDLER_H

#include <Arduino.h>

#include "ModbusSerial.h"
bool updatedByMaster = false;

ModbusSerial mb;

#define NUM_HREG 20

void updateData();

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
    pin(LED_BUILTIN, getBit(0, 0)); //SyncLED Control Bit
}

#endif