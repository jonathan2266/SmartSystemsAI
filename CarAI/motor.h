#pragma once
#include "Arduino.h"

class motor
{
public:
	void setup();
	motor(int pA1, int pA2, int pB1, int pB2);
	void LeftMotor(uint16_t speed, uint16_t direction);
	void RightMotor(uint16_t speed, uint16_t direction); //see the uit16 def
	uint16_t FORWARD = 0x1; 
	uint16_t BACKWARDS = 0x0;
	~motor();

private:
	prog_uint16_t motorPins[4];
	void motorCombined(uint8_t speed, uint16_t direction, uint8_t side);
};

