void joySetup(Joystick_ *Joystick)
{
  Joystick->setThrottleRange(0, 255);
  Joystick->setAcceleratorRange(0, 255);
  Joystick->setBrakeRange(0, 255);
  Joystick->setXAxisRange(0, 255);
  Joystick->setYAxisRange(0, 255);
  Joystick->setZAxisRange(0, 255);
  Joystick->setRxAxisRange(0, 255);
  Joystick->setRyAxisRange(0, 255);
  Joystick->setRzAxisRange(0, 255);
  Joystick->setRudderRange(0, 255);
  Joystick->setSteeringRange(0, 255);

  Joystick->begin(false);

  Joystick->setThrottle(127);
  Joystick->setAccelerator(127);
  Joystick->setBrake(127);
  Joystick->setXAxis(127);
  Joystick->setYAxis(127);
  Joystick->setZAxis(127);
  Joystick->setRxAxis(127);
  Joystick->setRyAxis(127);
  Joystick->setRzAxis(127);
  Joystick->setRudder(127);
  Joystick->setSteering(127);

  Joystick->sendState();
}

void setNSend(Joystick_ *Joystick, int clutch, int brake, int gas, int handbrake)
{
  Joystick->setYAxis(clutch);
  Joystick->setZAxis(brake);
  Joystick->setXAxis(gas);
  Joystick->setRxAxis(handbrake);
  Joystick->sendState();
}

void pinModes()
{
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
}

void serialHelp()
{
  Serial.println("Display - d; c,g,b; 0,1,l,h ");
  Serial.println("e.g. dc1 = display clutch true; dbl = display brake lower limit");
  Serial.println("Set - c,g,b; l,h; value");
  Serial.println("e.g. cl283 = clutch lower limit 283");
}

void serialHandler()
{
  byte pedalDisplay = EEPROM.read(16);
  String message, temp;
  char * pEnd;
  static char value[7];
  message = Serial.readString();
  temp = message.substring(2);
  temp.toCharArray(value, sizeof(value));
  // Serial.println(message.charAt(1));
  uint8_t addr = 0;
  switch (message.charAt(0))
  {
  case 'r':
    loadDefaults();
  break;
  case 'c':
    addr = ('l' == message.charAt(1)) ? 0 : 2;
    writeIntIntoEEPROM(addr, strtol(value, &pEnd, 10));
    break;
  case 'g':
    addr = ('l' == message.charAt(1)) ? 4 : 6;
    writeIntIntoEEPROM(addr, strtol(value, &pEnd, 10));
    break;
  case 'b':
    addr = ('l' == message.charAt(1)) ? 8 : 12;
    writeDoubleIntoEEPROM(addr, strtol(value, &pEnd, 10));
    break;
  case 'd':
    switch (message.charAt(1))
    {
    case 'c':
    // Serial.println("clutch");
      switch(message.charAt(2)){
        case '0':
        pedalDisplay &= 0b11111110;
        break;
        case '1':
        pedalDisplay |= 0b00000001;
        break;
        case 'l':
        Serial.print("Lower clutch limit: ");
        Serial.println(readIntFromEEPROM(0));
        break;
        case 'h':
        Serial.print("Upper clutch limit: ");
        Serial.println(readIntFromEEPROM(2));
        break;
        default:
        break;
      }
      break;
    case 'g':
    // Serial.println("gas");
    switch(message.charAt(2)){
        case '0':
        pedalDisplay &= 0b11111101;
        break;
        case '1':
        pedalDisplay |= 0b00000010;        
        break;
        case 'l':
        Serial.print("Lower gas limit:    ");
        Serial.println(readIntFromEEPROM(4));
        break;
        case 'h':
        Serial.print("Upper gas limit:    ");
        Serial.println(readIntFromEEPROM(6));
        break;
        default:
        break;
      }
      break;
    case 'b':
    // Serial.println("brake");
    switch(message.charAt(2)){
        case '0':
        pedalDisplay &= 0b11111011;
        break;
        case '1':
        pedalDisplay |= 0b00000100;
        break;
        case 'l':
        Serial.print("Lower brake limit:  ");
        Serial.println(readDoubleFromEEPROM(8));
        break;
        case 'h':
        Serial.print("Upper brake limit:  ");
        Serial.println(readDoubleFromEEPROM(12));
        break;
        default:
        break;
      }
      break;
    default:
      Serial.println("Invalid input");
      break;
    }
    break;
  default:
    Serial.println("Invalid input");
    break;
  }
  // Serial.println(readDoubleFromEEPROM(12),10);
  // Serial.println(strtol(value, &pEnd, 10));
  // Serial.println(pedalDisplay, BIN);
  EEPROM.write(16,pedalDisplay);
}