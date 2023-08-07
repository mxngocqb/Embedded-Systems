#include "Conmon.h"

// Hàm ghi dữ liệu nhiệt độ và thời gian vào EEPROM
void writeDataToEEPROM(int address, SensorData data) {
    EEPROM.put(address, data);
    EEPROM.commit();
}

// Hàm đọc dữ liệu nhiệt độ và thời gian từ EEPROM
void readDataFromEEPROM(int address, SensorData &data) {
    EEPROM.get(address, data);
}

// Hàm ghi dữ liệu nhiệt độ và thời gian vào EEPROM
void writeIntToEEPROM(int address, int data) {
    EEPROM.put(address, data);
    EEPROM.commit();
}

// Hàm đọc dữ liệu nhiệt độ và thời gian từ EEPROM
void readFromIntEEPROM(int address, int &data) {
    EEPROM.get(address, data);
}

// Hàm ghi dữ liệu nhiệt độ và thời gian vào EEPROM
void writeFloatToEEPROM(int address, float data) {
    EEPROM.put(address, data);
    EEPROM.commit();
}

// Hàm đọc dữ liệu nhiệt độ và thời gian từ EEPROM
void readFromfloatEEPROM(int address, float &data) {
    EEPROM.get(address, data);
}