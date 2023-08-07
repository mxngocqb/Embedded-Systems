// Sensor.cpp
#include "Sensor.h"
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

Sensor::Sensor() {}
Sensor::~Sensor() {}

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
uint8_t inputValue;

void Sensor::init()
{
	pinMode(DLS_PIN, INPUT);
	pinMode(BULB_PIN, OUTPUT);
	digitalWrite(BULB_PIN, HIGH);
	pinMode(FAN_PIN, OUTPUT);
	digitalWrite(FAN_PIN, HIGH);
	sensors.begin();
}

char tmp_str[20]; // Increase the size if needed

// Hàm gửi dữ liệu qua Serial về PC
void Sensor::sendDataToPC(SensorData data)
{
	Serial.print("Temp:");
	Serial.print(data.temp, 2);
	Serial.print("|Light:");
	Serial.println(data.light);
}

// Hàm đọc nhiệt độ từ DS18B20
float Sensor::readTemperature()
{
	sensors.requestTemperatures();
	return sensors.getTempCByIndex(0);
}

// Hàm đọc nhiệt độ từ DS18B20 và Quang tở
SensorData Sensor::readDataSensor()
{
	SensorData sensorData;
	inputValue = analogRead(DLS_PIN);
	sensorData.light = inputValue;
	sensors.requestTemperatures();
	sensorData.temp = sensors.getTempCByIndex(0);

	if (sensorData.temp == DEVICE_DISCONNECTED_C)
	{
		Serial.println("Error: Could not read temperature data");
		while (1)
			delay(10);
	}

	return sensorData;
}
