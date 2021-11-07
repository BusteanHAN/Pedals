void writeDoubleIntoEEPROM(int address, double number)
{ 
  union {
    double d;
    byte b[sizeof(double)];
  };
  d = number;
  for (size_t i = 0; i < 4; i++) EEPROM.write(address + i, b[i]);
}

double readDoubleFromEEPROM(int address)
{
  union {
    double d;
    byte b[sizeof(double)];
  };
  for (size_t i = 0; i < 4; i++) b[i] = EEPROM.read(address + i);
  return d;
}

void writeIntIntoEEPROM(int address, int number)
{ 
  union {
    int num;
    byte b[sizeof(int)];
  };
  num = number;
  EEPROM.write(address, b[0]);
  EEPROM.write(address + 1, b[1]);
}

int readIntFromEEPROM(int address)
{
  union {
    int num;
    byte b[sizeof(int)];
  };
  b[0] = EEPROM.read(address);
  b[1] = EEPROM.read(address + 1);
  return num;
}

bool checkEEPROMclear() {
  int val = 0;
  for (int i = 0; i < 1024; i++) val += EEPROM.read(i);
  if (!val) return true;
  else return false;
}

void loadDefaults() {
  writeIntIntoEEPROM(0,296);
  writeIntIntoEEPROM(2,400);
  writeIntIntoEEPROM(4,876);
  writeIntIntoEEPROM(6,682);
  writeDoubleIntoEEPROM(8,46000);
  writeDoubleIntoEEPROM(12,500000);
}

void clearEEPROM() {
  for (int i = 0; i < 1024; i++) EEPROM.write(i, 0);
}