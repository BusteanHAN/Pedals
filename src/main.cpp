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

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_MULTI_AXIS, 0, 0,
                   true, true, true, // X  Y  Z
                   true, true, true, //Rx Ry Rz
                   true, true, true, true, true); //Rudder, Throttle, Accelerator, Brake, Steering

long long currentmoment;
int gas[6];
int clutch[6];
double brake[6];
int handbrake, previoushandbrake, handbraketh = 1;

HX711 brakePedal;

void serialHandler();
void displayStuff();

void setup() {
  if (checkEEPROMclear()) loadDefaults();

  clutch[3] = 1; clutch[4] = readUint16_tFromEEPROM(0); clutch[5] = readUint16_tFromEEPROM(2);
  gas[3] = 1; gas[4] = readUint16_tFromEEPROM(4); gas[5] = readUint16_tFromEEPROM(6);
  brake[3] = 1; brake[4] = readDoubleFromEEPROM(8); brake[5] = readDoubleFromEEPROM(12);

  Serial.begin(115200);
  Serial.setTimeout(5);
  Serial1.begin(9600);
  brakePedal.begin(A1, A0);
  joySetup(&Joystick);
  pinModes();
  // clearEEPROM();
}

void loop()
{
  if (Serial.available())
  {
    serialHandler();
    clutch[4] = readUint16_tFromEEPROM(0); clutch[5] = readUint16_tFromEEPROM(2);
    gas[4] = readUint16_tFromEEPROM(4); gas[5] = readUint16_tFromEEPROM(6);
    brake[4] = readDoubleFromEEPROM(8); brake[5] = readDoubleFromEEPROM(12);
  }
  displayStuff();

  clutch[2] = clutch[1];
  clutch[1] = analogRead(A3);
  clutch[0] = map(clutch[1], clutch[4], clutch[5], 0, 255);

  if (brakePedal.is_ready())
  {
    brake[2] = brake[1];
    brake[1] = brakePedal.read();
    brake[0] = map(brake[1], brake[4], brake[5], 0, 255);
  }
  gas[2] = gas[1];
  gas[1] = analogRead(A2);
  gas[0] = map(gas[1], gas[4], gas[5], 0, 255);

  previoushandbrake = handbrake;
  if (Serial1.available())
    handbrake = Serial1.read();

  setNSend(&Joystick, clutch[0], brake[0], gas[0], handbrake);
}


void displayStuff()
{
  byte serialSettings = EEPROM.read(16);
  if (serialSettings != 0x0)
  {
    if ((serialSettings & 0b00000001) > 0)
    {
      Serial.print("Clutch ");
      Serial.print(clutch[1]);
      Serial.print("   ");
      Serial.println(clutch[0]);
    }
    if ((serialSettings & 0b00000010) > 0)
    {
      Serial.print("Gas ");
      Serial.print(gas[1]);
      Serial.print("   ");
      Serial.println(gas[0]);
    }
    if ((serialSettings & 0b00000100) > 0)
    {
      Serial.print("Brake ");
      Serial.print(brake[1]);
      Serial.print("   ");
      Serial.println(brake[0]);
    }
    if ((serialSettings & 0b00001000) > 0)
    {
      String outMessage = String(clutch[1]) + "|" + String(gas[1]) + "|" + String(brake[1]);
      Serial.println(outMessage);
      serialSettings &= 0b11110111;
      EEPROM.write(16, serialSettings);
    }
  }
}