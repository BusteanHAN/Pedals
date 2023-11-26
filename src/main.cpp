#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

#ifndef EEPROM_H
#define EEPROM_H
#include <EEPROM.h>
#endif

#ifndef JOYSTICK_H
#define JOYSTICK_H
#include "Joystick.h"
#endif

#ifndef HX711_H
#define HX711_H
#include "HX711.h"
#endif

#ifndef EEPROMUTILS_H
#define EEPROMUTILS_H
#include "EEPROMUtils.h"
#endif

#ifndef CUSTOMSETUP_H
#define CUSTOMSETUP_H
#include "customSetup.h"
#endif

#ifndef BSTPEDALS_H
#define BSTPEDALS_H
#include "../pedalClasses/BSTPedals.h"
#endif

#define CLUTCH_PIN A3
#define GAS_PIN A2
#define BRAKE_DOUT_PIN A1
#define BRAKE_SCK_PIN A0

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_MULTI_AXIS, 0, 0,
                   true, true, true, // X  Y  Z
                   true, true, true, //Rx Ry Rz
                   true, true, true, true, true); //Rudder, Throttle, Accelerator, Brake, Steering

BSTPedals_ BSTPedals(CLUTCH_PIN, GAS_PIN, BRAKE_DOUT_PIN, BRAKE_SCK_PIN, Joystick);



long long currentmoment;
int gas[6];
int clutch[6];
double brake[6];
int handbrake, previoushandbrake, handbraketh = 1;

HX711 brakePedal;

void serialHandler();
void displayStuff();

void setup() {
  ;
}

void loop()
{
  BSTPedals.Worker();
}