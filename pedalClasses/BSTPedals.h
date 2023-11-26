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

class BSTPedals_
{
public:
  BSTPedals_(){};

  BSTPedals_(uint8_t clutchPin, uint8_t gasPin, uint8_t brakeDoutPin, uint8_t brakeSckPin)
      : clutch(clutchPin, 0),
        gas(gasPin, clutch.getLastUsedEEPROMAddress()),
        brake(brakeDoutPin, brakeSckPin, gas.getLastUsedEEPROMAddress())
  {
    this->Joystick = Joystick_(JOYSTICK_DEFAULT_REPORT_ID,
                               JOYSTICK_TYPE_MULTI_AXIS, 0, 0,
                               true, true, true,              // X  Y  Z
                               true, true, true,              // Rx Ry Rz
                               true, true, true, true, true); // Rudder, Throttle, Accelerator, Brake, Steering
    joySetup();
    clutch = Pedal_(clutchPin, 0);
    gas = Pedal_(gasPin, clutch.getLastUsedEEPROMAddress());
    brake = BrakePedal_(brakeDoutPin, brakeSckPin, gas.getLastUsedEEPROMAddress());
  };

  void Worker();

  void joySetup();

  // Getters for the pointers to the pedals
  Pedal_ *getClutch() { return &clutch; };
  Pedal_ *getGas() { return &gas; };
  BrakePedal_ *getBrake() { return &brake; };

private:
  Joystick_ Joystick;
  Pedal_ clutch;
  Pedal_ gas;
  BrakePedal_ brake;
};