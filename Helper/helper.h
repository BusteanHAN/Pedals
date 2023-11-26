enum pedatType{
    CLUTCH,
    BRAKE,
    GAS
};

enum valueType{
    RAW_VALUE,
    PREVIOUS_RAW_VALUE,
    MAPPED_VALUE,
    LIMIT_LOWER,
    LIMIT_UPPER,
    EEPROM_BASE_ADDRESS
};

enum commands{
    HELP = 0x01,
    CLEAR = 0x02,
    SET = 0x03,
    READ = 0x04,
    REQUESTALL = 0x05,
    SAVEEEP = 0x06,
    READEEP = 0x07,
};