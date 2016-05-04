#pragma once
#include "Arduino.h"

class sensor
{
public:
	sensor(uint16_t sensorEchoPin[4] ,uint16_t sensorTrigPin[4]);
	uint8_t SenF = 0;
	uint8_t SenL = 1;
	uint8_t SenR = 2;
	uint8_t SenExtra = 3;

	void fillSensors(uint8_t code);
	uint8_t GetSensorData(uint8_t number);
	~sensor();

private:
	uint16_t sensorEchoPin[4];
	uint16_t sensorTrigPin[4];
	int sensorDataEcho[4] = { -1,-1,-1,-1 };

	int echo(uint8_t echoPin, uint8_t trigPin);
};

