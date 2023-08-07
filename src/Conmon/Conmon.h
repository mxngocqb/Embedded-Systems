#ifndef _CONMON_H_
#define _CONMON_H_
#include <Arduino.h>
#include <EEPROM.h>
#include "..\Sensor\Sensor.h"
/**
 * @brief read/write data form/to EEPROM
 *
 * @param s_address start address in EEPROM
 * @param length number of byte readed/write
 * @param value  byte array readed/write form/to EEPROM
 */
void writeDataToEEPROM(int address, SensorData data);
void readDataFromEEPROM(int address, SensorData &data);
void writeIntToEEPROM(int address, int data);
void readFromIntEEPROM(int address, int &data);
void writeFloatToEEPROM(int address, float data);
void readFromfloatEEPROM(int address, float &data);
#endif
