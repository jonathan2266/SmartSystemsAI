// 
// 
// 

#include "servo.h"

void ServoClass::init()
{
	
	myservo.attach(9);  // attaches the servo on pin 9 to the servo object
	Serial.begin(9600);
}

void ServoClass::loop() 
{
	if (lineType == 1) { // dotted line
		val = 100;
		myservo.write(val);
		delay(195.25);     // waits for the servo to get there  
		val = 80;
		myservo.write(val);
		delay(200);
	}
	else if (lineType == 2) { // full line
		val = 90;
		myservo.write(val);
	}
}

