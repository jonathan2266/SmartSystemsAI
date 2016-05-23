#include "servoCar.h"

//Servo myservo;
uint8_t servoPin;

servoCar::servoCar(uint8_t intPin)
{
	//myservo.attach(intPin);
	servoPin = intPin;
	pinMode(intPin, OUTPUT);
}

void servoCar::lineCont()
{
	digitalWrite(servoPin, HIGH);
	delayMicroseconds(0);
	digitalWrite(servoPin, LOW);
	/*myservo.write(90);*/
}

void servoCar::lineDash()
{
	//digitalWrite(servoPin, HIGH);
	//delayMicroseconds(0);
	//digitalWrite(servoPin, LOW);
	//delay(200);
	//digitalWrite(servoPin, HIGH);
	//delayMicroseconds(1500);
	//digitalWrite(servoPin, LOW);
	//delay(200);
	//myservo.write(90);
	//delay(200);
	//myservo.write(90);
	//delay(196);

	digitalWrite(servoPin, HIGH);
	delayMicroseconds(0);
	digitalWrite(servoPin, LOW);

}

void servoCar::line(bool mode) {
	Serial.println("Servo Called");
	if (mode = true)
	{
		lineDash();
	}
	else
	{
		lineCont();
	}
}
