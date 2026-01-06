#ifndef Encoder_h
#define Encoder_h

#include <Arduino.h>



//Encoder Class
class Encoder {
    public:
        //Initialize Encoder with Pin A, Pin B and a callback function which calls update
        Encoder(uint8_t pinA, uint8_t pinB/*,callback_function_t callback*/);
        //Returns Current Encoder Position
        int32_t read(void);
        //Set Encoder Position
        void write(int32_t pos);
        //Updates Encoder Postion on Interrupt
        void update(void);
        //SetEncoder Resolution
        void setResolution(float res);
        //Get Encoder Resolution
        float getResolution(void);
        //Set Position Correction
        void setCorrection(float corr);
        //Get Position Correction
        float getCorrection(void);
        //GetMovement in float
        float getPos(void);
        //set Position
        void setPos(float pos);
    private:
        int32_t _position;
        uint8_t _pinA;
        uint8_t _pinB;
        uint8_t _state;
        //callback_function_t _callback;
        float _res;
        float _corr;
};
#endif