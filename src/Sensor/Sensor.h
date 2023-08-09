// Sensor.h

#ifndef _SENSOR_H_
#define _SENSOR_H_

#include "SHT1x/SHT1x.h"

#define ONE_WIRE_BUS 2
#define DLS_PIN A0
#define BULB_PIN D5
#define FAN_PIN D6
#define CHANGE_MODE D3

#define SW_FAN D7
#define SW_BULB D8

#define MIN_ADDR_DATA 12
#define MAX_ADDR_DATA 172

typedef struct
{
	uint8_t light;
	float temp;
} SensorData;

class Sensor
{
public:
	Sensor();
	~Sensor();
	void init();
	char *convertDayToStr(SensorData data);
	char *convertTimeToStr(SensorData data);
	char *convertAllToStr(SensorData data);
	float readTemperature();
	SensorData readDataSensor();
	void sendDataToPC(SensorData data);
};

#endif
