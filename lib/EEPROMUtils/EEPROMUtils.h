void writeLongIntoEEPROM(const uint8_t address, const long number)
{ 
  union {
    long d;\
    byte b[sizeof(long)];
  };
  d = number;
  for (size_t i = 0; i < sizeof(long); i++) EEPROM.write(address + i, b[i]);
}

long readLongFromEEPROM(const int address)
{
  union {
    long l;
    byte b[sizeof(long)];
  };
  for (size_t i = 0; i < sizeof(long); i++) b[i] = EEPROM.read(address + i);
  return l;
}

void writeUint16_tToEEPROM(const uint8_t address, const uint16_t number)
{ 
  union {
    uint16_t num;
    byte b[sizeof(uint16_t)];
  };
  num = number;
  EEPROM.write(address, b[0]);
  EEPROM.write(address + 1, b[1]);
}

uint16_t readUint16_tFromEEPROM(const uint16_t address)
{
  union {
    uint16_t num;
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
  writeUint16_tToEEPROM(0,296);
  writeUint16_tToEEPROM(2,400);
  writeUint16_tToEEPROM(4,876);
  writeUint16_tToEEPROM(6,682);
  writeLongIntoEEPROM(8,46000);
  writeLongIntoEEPROM(12,500000);
}

void clearEEPROM() {
  for (int i = 0; i < 1024; i++) EEPROM.write(i, 0);
}