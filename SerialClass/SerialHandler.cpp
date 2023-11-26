#include "SerialHandler.h"

#ifndef HELPER_H
#define HELPER_H
#include "../Helper/helper.h"
#endif

void SerialHandler::Worker()
{
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
                    pBSTPedals->getClutch()->setLowerLimit(readUint16_tFromSerial(serialBuffer));
                    break;

                case LIMIT_UPPER:
                    pBSTPedals->getClutch()->setUpperLimit(readUint16_tFromSerial(serialBuffer));
                    break;

                default:
                    break;
                }
                break;

            case GAS:
                switch (serialBuffer[2])
                {
                case LIMIT_LOWER:
                    pBSTPedals->getGas()->setLowerLimit(readUint16_tFromSerial(serialBuffer));
                    break;

                case LIMIT_UPPER:
                    pBSTPedals->getGas()->setUpperLimit(readUint16_tFromSerial(serialBuffer));
                    break;

                default:
                    break;
                }
                break;

            case BRAKE:
                switch (serialBuffer[2])
                {
                case LIMIT_LOWER:
                    pBSTPedals->getBrake()->setLowerLimit(readLongFromSerial(serialBuffer));
                    break;

                case LIMIT_UPPER:
                    pBSTPedals->getBrake()->setUpperLimit(readLongFromSerial(serialBuffer));
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
                    Serial.println(pBSTPedals->getClutch()->getLowerLimit());
                    break;

                case LIMIT_UPPER:
                    Serial.print("cu: ");
                    Serial.println(pBSTPedals->getClutch()->getUpperLimit());
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
                    Serial.println(pBSTPedals->getBrake()->getLowerLimit());
                    break;

                case LIMIT_UPPER:
                    Serial.print("bu: ");
                    Serial.println(pBSTPedals->getBrake()->getUpperLimit());
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
                    Serial.println(pBSTPedals->getGas()->getLowerLimit());
                    break;

                case LIMIT_UPPER:
                    Serial.print("gu: ");
                    Serial.println(pBSTPedals->getGas()->getUpperLimit());
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
            outString += pBSTPedals->getClutch()->getmappedValue();
            outString += "|";
            outString += pBSTPedals->getGas()->getmappedValue();
            outString += "|";
            outString += pBSTPedals->getBrake()->getmappedValue();
            Serial.println(outString);
            break;
        }

        case SAVEEEP:
        {
            pBSTPedals->getClutch()->saveToEEPROM();
            pBSTPedals->getGas()->saveToEEPROM();
            pBSTPedals->getBrake()->saveToEEPROM();
            break;
        }

        case READEEP:
        {
            pBSTPedals->getClutch()->loadFromEEPROM();
            pBSTPedals->getGas()->loadFromEEPROM();
            pBSTPedals->getBrake()->loadFromEEPROM();
            break;
        }
        };
    }
}

uint8_t SerialHandler::readUint8_tFromSerial(byte serialBuffer[])
{
    return (uint8_t)serialBuffer[3];
}

uint16_t SerialHandler::readUint16_tFromSerial(byte serialBuffer[])
{
    return (uint16_t)serialBuffer[3] << 8 | (uint16_t)serialBuffer[4];
}

long SerialHandler::readLongFromSerial(byte serialBuffer[])
{
    return (long)serialBuffer[3] << 24 | (long)serialBuffer[4] << 16 | (long)serialBuffer[5] << 8 | (long)serialBuffer[6];
}

void SerialHandler::clearEEPROM()
{
    for (int i = 0; i < 1024; i++)
    {
        EEPROM.write(i, 0);
    }
}