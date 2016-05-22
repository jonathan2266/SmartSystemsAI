#pragma once
#include "Arduino.h"
#include <Servo.h> //servo library

class ServoClass
{
 public:
	 Servo myservo;  // create servo object to control a servo
	 int val;    //value to write to servo
	 int lineType = 1;
	void init();
	void loop();
};