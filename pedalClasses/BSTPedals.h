#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

#ifndef PEDAL_H
#define PEDAL_H
#include "Pedal.h"
#endif

#ifndef BRAKEPEDAL_H
#define BRAKEPEDAL_H
#include "BrakePedal.h"
#endif

#ifndef JOYSTICK_H
#define JOYSTICK_H
#include "Joystick.h"
#endif

#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H
#include "../SerialClass/SerialHandler.h"
#endif

class BSTPedals
{
public:
    BSTPedals(uint8_t clutchPin,
              uint8_t gasPin,
              uint8_t brakeDoutPin,
              uint8_t brakeSckPin,
              Joystick_ Joystick)
        : clutch(clutchPin, 0),
          gas(gasPin, clutch.getLastUsedEEPROMAddress()),
          brake(brakeDoutPin, brakeSckPin, gas.getLastUsedEEPROMAddress()),
          Joystick(&Joystick) {
            serialHandler = SerialHandler(*this);
          }

    void Worker();

    void joySetup();

    // Getters for the pointers to the pedals
    Pedal *getClutch() { return &clutch; }
    Pedal *getGas() { return &gas; }
    BrakePedal *getBrake() { return &brake; }

private:
    SerialHandler serialHandler;
    Joystick_ *Joystick;
    Pedal clutch;
    Pedal gas;
    BrakePedal brake;
};