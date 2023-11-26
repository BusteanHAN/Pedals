#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

#ifndef EEPROM_H
#define EEPROM_H
#include <EEPROM.h>
#endif

#ifndef EEPROMUTILS_H
#define EEPROMUTILS_H
#include "EEPROMUtils.h"
#endif

class Pedal
{
public:
    Pedal() {}

    Pedal(uint8_t pin, uint8_t eepromBaseAddress) : pin(pin), eepromBaseAddress(eepromBaseAddress)
    {
        pinMode(pin, INPUT);
        loadFromEEPROM();
    }

    void assignPin(uint8_t newPin);

    void setUpperLimit(uint16_t newUpperLimit);
    uint16_t getUpperLimit() const;
    void setLowerLimit(uint16_t newLowerLimit);
    uint16_t getLowerLimit() const;

    void setValue(uint16_t newPosition);
    void updatePreviousValue();
    uint16_t getPreviousValue() const;

    void mapValue();
    uint8_t getmappedValue() const;

    void setEEPROMBaseAddress(uint8_t newEEPROMBaseAddress);
    uint8_t getEEPROMBaseAddress() const;
    void saveToEEPROM();
    void loadFromEEPROM();
    uint8_t getLastUsedEEPROMAddress() const;

    void Worker();

private:
    uint8_t pin;

    uint16_t upperLimit = 0;
    uint16_t lowerLimit = 0;

    uint16_t rawValue = 0;
    uint16_t previousRawValue = 255;

    uint8_t mappedValue = 0;

    uint8_t eepromBaseAddress;
};