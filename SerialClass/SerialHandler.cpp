#include "SerialHandler.h"

#ifndef HELPER_H
#define HELPER_H
#include "../Helper/helper.h"
#endif

void SerialHandler_::Worker()
{
    BSTPedals.Worker();
    if (Serial.available())
    {
        Serial.readBytes(serialBuffer, 32);
        String outString = "";

        switch (serialBuffer[0])
        {
        case HELP:
        {
            outString += "Display - d; c,g,b; 0,1,l,h \n";
            outString += "e.g. dc1 = display clutch true; dbl = display brake lower limit \n";
            outString += "Set - c,g,b; l,h; value \n";
            outString += "e.g. cl283 = clutch lower limit 283 \n";

            Serial.println(outString);

            break;
        }

        case CLEAR:
        {
            clearEEPROM();
            Serial.println("EEPROM cleared");
            break;
        }

        case SET:
        {
            switch (serialBuffer[1])
            {
            case CLUTCH:
                switch (serialBuffer[2])
                {
                case LIMIT_LOWER:
                    BSTPedals.getClutch()->setLowerLimit(readUint16_tFromSerial(serialBuffer));
                    break;

                case LIMIT_UPPER:
                    BSTPedals.getClutch()->setUpperLimit(readUint16_tFromSerial(serialBuffer));
                    break;

                default:
                    break;
                }
                break;

            case GAS:
                switch (serialBuffer[2])
                {
                case LIMIT_LOWER:
                    BSTPedals.getGas()->setLowerLimit(readUint16_tFromSerial(serialBuffer));
                    break;

                case LIMIT_UPPER:
                    BSTPedals.getGas()->setUpperLimit(readUint16_tFromSerial(serialBuffer));
                    break;

                default:
                    break;
                }
                break;

            case BRAKE:
                switch (serialBuffer[2])
                {
                case LIMIT_LOWER:
                    BSTPedals.getBrake()->setLowerLimit(readLongFromSerial(serialBuffer));
                    break;

                case LIMIT_UPPER:
                    BSTPedals.getBrake()->setUpperLimit(readLongFromSerial(serialBuffer));
                    break;

                default:
                    break;
                }
                break;

            default:
                break;
            }
            break;
        }

        case READ:
        {
            switch (serialBuffer[1])
            {
            case CLUTCH:
                switch (serialBuffer[2])
                {
                case LIMIT_LOWER:
                    Serial.print("cl ");
                    Serial.println(BSTPedals.getClutch()->getLowerLimit());
                    break;

                case LIMIT_UPPER:
                    Serial.print("cu: ");
                    Serial.println(BSTPedals.getClutch()->getUpperLimit());
                    break;

                default:
                    break;
                }
                break;

            case BRAKE:
                switch (serialBuffer[2])
                {
                case LIMIT_LOWER:
                    Serial.print("bl: ");
                    Serial.println(BSTPedals.getBrake()->getLowerLimit());
                    break;

                case LIMIT_UPPER:
                    Serial.print("bu: ");
                    Serial.println(BSTPedals.getBrake()->getUpperLimit());
                    break;

                default:
                    break;
                }
                break;

            case GAS:
                switch (serialBuffer[2])
                {
                case LIMIT_LOWER:
                    Serial.print("gl: ");
                    Serial.println(BSTPedals.getGas()->getLowerLimit());
                    break;

                case LIMIT_UPPER:
                    Serial.print("gu: ");
                    Serial.println(BSTPedals.getGas()->getUpperLimit());
                    break;

                default:
                    break;
                }
                break;

            default:
                break;
            }
            break;
        }

        case REQUESTALL:
        {
            outString += BSTPedals.getClutch()->getmappedValue();
            outString += "|";
            outString += BSTPedals.getGas()->getmappedValue();
            outString += "|";
            outString += BSTPedals.getBrake()->getmappedValue();
            Serial.println(outString);
            break;
        }

        case SAVEEEP:
        {
            BSTPedals.getClutch()->saveToEEPROM();
            BSTPedals.getGas()->saveToEEPROM();
            BSTPedals.getBrake()->saveToEEPROM();
            break;
        }

        case READEEP:
        {
            BSTPedals.getClutch()->loadFromEEPROM();
            BSTPedals.getGas()->loadFromEEPROM();
            BSTPedals.getBrake()->loadFromEEPROM();
            break;
        }
        };
    }
}

uint8_t SerialHandler_::readUint8_tFromSerial(byte serialBuffer[])
{
    return (uint8_t)serialBuffer[3];
}

uint16_t SerialHandler_::readUint16_tFromSerial(byte serialBuffer[])
{
    return (uint16_t)serialBuffer[3] << 8 | (uint16_t)serialBuffer[4];
}

long SerialHandler_::readLongFromSerial(byte serialBuffer[])
{
    return (long)serialBuffer[3] << 24 | (long)serialBuffer[4] << 16 | (long)serialBuffer[5] << 8 | (long)serialBuffer[6];
}

void SerialHandler_::clearEEPROM()
{
    for (int i = 0; i < 1024; i++)
    {
        EEPROM.write(i, 0);
    }
}