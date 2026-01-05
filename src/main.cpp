#define SERIAL_RX_BUFFER_SIZE 256
#define SERIAL_TX_BUFFER_SIZE 256

#include <Arduino.h>
#include "initIO.h"
#include "modBusHandler.h"


HardwareSerial Serial3(PB11, PB10);
void setup() {
    initIO();
    setupModbus();
}



void loop() {
    mbPoll();
}


