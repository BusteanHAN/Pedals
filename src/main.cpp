#define CLUTCH_PIN A3
#define GAS_PIN A2
#define BRAKE_DOUT_PIN A1
#define BRAKE_SCK_PIN A0

#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

#ifndef EEPROM_H
#define EEPROM_H
#include <EEPROM.h>
#endif

#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H
#include "../SerialClass/SerialHandler.h"
#endif

#ifndef HELPER_H
#define HELPER_H
#include "../Helper/helper.h"
#endif

SerialHandler_ SerialHandler;

void setup() {}

void loop()
{
  SerialHandler.Worker();
}