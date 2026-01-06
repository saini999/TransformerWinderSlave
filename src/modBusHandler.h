#ifndef MODBUS_HANDLER_H
#define MODBUS_HANDLER_H

#include <Arduino.h>

#include "ModbusSerial.h"
#include "regDef.h"

#define NUM_HREG 20

void updateData();

void setupModbus();

void mbPoll();

inline bool getBit(uint16_t regIdx, uint8_t bitIdx);

inline void setBit(uint16_t regIdx, uint8_t bitIdx, bool value);

inline void setFloat(uint16_t regIdx, float value);

inline float getFloat(uint16_t regIdx);
void fetchDataFromRegisters();
void sendDataToRegisters();


void updateData();

#endif