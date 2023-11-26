#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

#ifndef BSTPEDALS_H
#define BSTPEDALS_H
#include "../pedalClasses/BSTPedals.h"
#endif

#ifndef HELPER_H
#define HELPER_H
#include "../Helper/helper.h"
#endif

class SerialHandler_
{
public:
    SerialHandler_()
    {
        Serial.begin(115200);
        Serial.setTimeout(5);
        this->BSTPedals = BSTPedals_(CLUTCH_PIN, GAS_PIN, BRAKE_DOUT_PIN, BRAKE_SCK_PIN);
    };
    void Worker();
    uint8_t readUint8_tFromSerial(byte serialBuffer[]);
    uint16_t readUint16_tFromSerial(byte serialBuffer[]);
    long readLongFromSerial(byte serialBuffer[]);
    void clearEEPROM();

private:
    byte serialBuffer[32];
    BSTPedals_ BSTPedals;
};