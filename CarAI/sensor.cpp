#include "sensor.h"

#define SENSORCOUNT 4

sensor::sensor(uint16_t sensorEchoPin[4], uint16_t sensorTrigPin[4])
{

	__sensorDataEcho[0] = 200;
	__sensorDataEcho[1] = 20;
	__sensorDataEcho[2] = 200;
	__sensorDataEcho[3] = 200;

	for (size_t i = 0; i < SENSORCOUNT; i++)
	{
		pinMode(sensorEchoPin[i], INPUT);
		pinMode(sensorTrigPin[i], OUTPUT);
		__sensorEchoPin = sensorEchoPin;
		__sensorTrigPin = sensorTrigPin;
	}
}

void sensor::fillSensors(uint8_t code) {
	//echo has to be replaced by echoFront/echoSide
	if (code == 5)
	{
		for (int i = 0; i < sizeof(__sensorDataEcho) / sizeof(__sensorDataEcho[0]); i++)
		{
			__sensorDataEcho[i] = echo(__sensorEchoPin[i],__sensorTrigPin[i]);
		}
	}
	else
	{
		__sensorDataEcho[code] = echo(__sensorEchoPin[code], __sensorTrigPin[code]);
	}

}

uint8_t sensor::GetSensorData(uint8_t number)
{
	return uint8_t(__sensorDataEcho[number]);
}

int sensor::echo(uint8_t echoPin, uint8_t trigPin)
{
	uint16_t maximumRange = 200; // Maximum range needed
	uint16_t minimumRange = 0; // Minimum range needed
	uint16_t duration, distance; // Duration used to calculate distance

	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);

	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);

	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);

	//Calculate the distance (in cm) based on the speed of sound.
	distance = duration / 58.2;

	if (distance >= maximumRange || distance <= minimumRange) {
		/* Send a negative number to computer and Turn LED ON
		to indicate "out of range" */
		Serial.println("maxVal sensor");
		Serial.println(distance);
		return uint8_t(255);
	}
	else {
		/* Send the distance to the computer using Serial protocol, and
		turn LED OFF to indicate successful reading. */
		Serial.println(distance);
		return uint8_t(distance);
	}
}



sensor::~sensor()
{
	delete __sensorEchoPin;
	delete __sensorTrigPin;
	delete __sensorDataEcho;
}

