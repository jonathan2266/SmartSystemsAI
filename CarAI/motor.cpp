#include "motor.h"

#define MAXPWM 255

motor::motor(int pA1, int pA2, int pB1, int pB2)
{
	motorPins[0] = pA1;
	motorPins[1] = pA2;
	motorPins[2] = pB1;
	motorPins[3] = pB2;

}

void motor::setup() {

	for (size_t i = 0; i < sizeof(motorPins) / sizeof(motorPins[0]); i++)
	{
		pinMode(motorPins[i], OUTPUT);
	}
}

void motor::motorCombined(uint8_t speed, uint16_t direction, uint8_t side)
{

	if (direction == FORWARD)
	{
		if (speed == MAXPWM)
		{
			digitalWrite(motorPins[0 + side], HIGH);
			digitalWrite(motorPins[1 + side], LOW);

		}
		else if(speed == 0)
		{
			digitalWrite(motorPins[0 + side], LOW);
			digitalWrite(motorPins[1 + side], LOW);
		}
		else
		{
			analogWrite(motorPins[0 + side], speed);
			digitalWrite(motorPins[1 + side], LOW);
		}
	}
	if (direction == motor::BACKWARDS)
	{
		if (speed == MAXPWM)
		{
			digitalWrite(motorPins[0 + side], LOW);
			digitalWrite(motorPins[1 + side], HIGH);
		}
		else if (speed == 0)
		{
			digitalWrite(motorPins[0 + side], LOW);
			digitalWrite(motorPins[1 + side], LOW);
		}
		else
		{
			digitalWrite(motorPins[0 + side], LOW);
			analogWrite(motorPins[1 + side], speed);
		}
	}
}

void motor::LeftMotor(uint16_t speed, uint16_t direction)
{
	motorCombined(speed, direction, 0);
}

void motor::RightMotor(uint16_t speed, uint16_t direction)
{
	motorCombined(speed, direction, 2);
}


motor::~motor()
{
	delete motorPins;
}


