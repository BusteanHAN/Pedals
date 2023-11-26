#include "pedal.h"

void Pedal_::assignPin(uint8_t newPin)
{
    pin = newPin;
}


void Pedal_::setUpperLimit(uint16_t newUpperLimit)
{
    upperLimit = newUpperLimit;
}

void Pedal_::setLowerLimit(uint16_t newLowerLimit)
{
    lowerLimit = newLowerLimit;
}


void Pedal_::setValue(uint16_t newValue)
{
    rawValue = newValue;
}

void Pedal_::updatePreviousValue()
{
    previousRawValue = rawValue;
}

uint16_t Pedal_::getPreviousValue() const
{
    return previousRawValue;
}


void Pedal_::mapValue()
{
    mappedValue = map(rawValue, lowerLimit, upperLimit, 0, 255);
}

uint8_t Pedal_::getmappedValue() const
{
    return mappedValue;
}


void Pedal_::setEEPROMBaseAddress(uint8_t newEEPROMBaseAddress)
{
    eepromBaseAddress = newEEPROMBaseAddress;
}

uint8_t Pedal_::getEEPROMBaseAddress() const
{
    return eepromBaseAddress;
}

void Pedal_::saveToEEPROM()
{
    EEPROM.put(eepromBaseAddress, lowerLimit);
    EEPROM.put(eepromBaseAddress + sizeof(lowerLimit), upperLimit);
}

void Pedal_::loadFromEEPROM()
{
    EEPROM.get(eepromBaseAddress, lowerLimit);
    EEPROM.get(eepromBaseAddress + sizeof(lowerLimit), upperLimit);
}

uint8_t Pedal_::getLastUsedEEPROMAddress() const
{
    return eepromBaseAddress + sizeof(lowerLimit) + sizeof(upperLimit);
}


void Pedal_::Worker()
{
    Pedal_::updatePreviousValue();
    Pedal_::setValue(analogRead(pin));
    Pedal_::mapValue();
}