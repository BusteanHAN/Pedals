#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

#ifndef PEDAL_H
#define PEDAL_H
#include "Pedal.h"
#endif

#ifndef HX711_H
#define HX711_H
#include "HX711.h"
#endif

class BrakePedal : public Pedal
{
public:
    BrakePedal(uint8_t hx711DoutPin, uint8_t hx711SckPin, uint8_t eepromBaseAddress)
    {
        hx711.begin(hx711DoutPin, hx711SckPin);
        setEEPROMBaseAddress(eepromBaseAddress);
        loadFromEEPROM();
    }

    void Worker()
    {
        if (hx711.is_ready())
        {
            updatePreviousValue();
            setValue(hx711.read());
            mapValue();
        }
    }

private:
    HX711 hx711;
    long rawValue = 0;
    long previousRawValue = 255;
    long upperLimit = 0;
    long lowerLimit = 0;
};
