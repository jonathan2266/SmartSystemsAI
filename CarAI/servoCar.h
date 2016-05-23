#pragma once
#include "Arduino.h"
//#include "Servo.h"

class servoCar
{
public:
	servoCar(uint8_t intPin);
	void lineCont();
	void lineDash();
	void line(bool mode);
};
