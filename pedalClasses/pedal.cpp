#include "pedal.h"

void Pedal::assignPin(uint8_t newPin)
{
    pin = newPin;
}


void Pedal::setUpperLimit(uint16_t newUpperLimit)
{
    upperLimit = newUpperLimit;
}

void Pedal::setLowerLimit(uint16_t newLowerLimit)
{
    lowerLimit = newLowerLimit;
}


void Pedal::setValue(uint16_t newValue)
{
    rawValue = newValue;
}

void Pedal::updatePreviousValue()
{
    previousRawValue = rawValue;
}

uint16_t Pedal::getPreviousValue() const
{
    return previousRawValue;
}


void Pedal::mapValue()
{
    mappedValue = map(rawValue, lowerLimit, upperLimit, 0, 255);
}

uint8_t Pedal::getmappedValue() const
{
    return mappedValue;
}


void Pedal::setEEPROMBaseAddress(uint8_t newEEPROMBaseAddress)
{
    eepromBaseAddress = newEEPROMBaseAddress;
}

uint8_t Pedal::getEEPROMBaseAddress() const
{
    return eepromBaseAddress;
}

void Pedal::saveToEEPROM()
{
    EEPROM.put(eepromBaseAddress, lowerLimit);
    EEPROM.put(eepromBaseAddress + sizeof(lowerLimit), upperLimit);
}

void Pedal::loadFromEEPROM()
{
    EEPROM.get(eepromBaseAddress, lowerLimit);
    EEPROM.get(eepromBaseAddress + sizeof(lowerLimit), upperLimit);
}

uint8_t Pedal::getLastUsedEEPROMAddress() const
{
    return eepromBaseAddress + sizeof(lowerLimit) + sizeof(upperLimit);
}


void Pedal::Worker()
{
    Pedal::updatePreviousValue();
    Pedal::setValue(analogRead(pin));
    Pedal::mapValue();
}