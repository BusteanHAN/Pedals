#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

#ifndef BSTPEDALS_H
#define BSTPEDALS_H
#include "../pedalClasses/BSTPedals.h"
#endif

class SerialHandler
{
public:
    SerialHandler() {}

    SerialHandler(BSTPedals_ pBSTPedals) : pBSTPedals(&pBSTPedals) {
        Serial.begin(115200);
        Serial.setTimeout(5);
    }
    void Worker();
    uint8_t readUint8_tFromSerial(byte serialBuffer[]);
    uint16_t readUint16_tFromSerial(byte serialBuffer[]);
    long readLongFromSerial(byte serialBuffer[]);
    void clearEEPROM();

private:
    byte serialBuffer[32];
    BSTPedals_ *pBSTPedals;
};