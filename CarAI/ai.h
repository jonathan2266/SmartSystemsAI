#pragma once
#include "Arduino.h"
#include "ai.h"
#include "sensor.h"
#include "motor.h"


class ai
{
public:
	ai();
	~ai();
	void setup();
	void start();
private:
	void checkSurroundings(uint8_t mode);
	void startLeftCircle();
	void motorStop();
	void spinLeft(uint8_t speed);
	void spinRight(uint8_t speed);
	void engineForward(uint8_t speed);

	uint32_t snapshot;
	int sensorData[4] = {-1,-1,-1,-1};
};

