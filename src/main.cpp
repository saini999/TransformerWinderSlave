#define SERIAL_RX_BUFFER_SIZE 256
#define SERIAL_TX_BUFFER_SIZE 256
#define USE_HOLDING_REGISTERS_ONLY
#include <Arduino.h>
#include "initIO.h"
#include "modBusHandler.h"
#include "regDef.h"



void setup() {
    initIO();
    setupModbus();
}



void loop() {
    mbPoll();
    runTasks();
    clearControl();
}


