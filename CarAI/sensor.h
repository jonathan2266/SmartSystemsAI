#pragma once
#include "Arduino.h"

class sensor
{
public:
	sensor(uint16_t sensorEchoPin[4] ,uint16_t sensorTrigPin[4]);
	uint8_t SenF = 0x0;
	uint8_t SenL = 0x1;
	uint8_t SenR = 0x2;
	uint8_t SenExtra = 0x3;

	void fillSensors(uint8_t code);
	uint8_t GetSensorData(uint8_t number);
	~sensor();

private:
	uint16_t sensorEchoPin[4];
	uint16_t sensorTrigPin[4];
	uint16_t sensorDataEcho[4] = { -1,-1,-1,-1 };

	uint16_t echo(uint8_t echoPin, uint8_t trigPin);
};

