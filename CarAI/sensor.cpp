#include "sensor.h"

sensor::sensor(uint16_t sensorEchoPin[4], uint16_t sensorTrigPin[4])
{
	for (size_t i = 0; i < sizeof(sensorEchoPin)/sizeof(sensorEchoPin[0]); i++)
	{
		pinMode(sensorEchoPin[i], OUTPUT);
		pinMode(sensorTrigPin[i], INPUT);
	}
}

void sensor::fillSensors(uint8_t code) {
	//echo has to be replaced by echoFront/echoSide
	if (code == 5)
	{
		for (int i = 0; i < sizeof(sensorDataEcho) / sizeof(sensorDataEcho[0]); i++)
		{
			sensorDataEcho[i] = echo(sensorEchoPin[i],sensorTrigPin[i]);
		}
	}
	else
	{
		sensorDataEcho[code] = echo(sensorEchoPin[code], sensorTrigPin[code]);
	}

}

uint16_t sensor::echo(uint8_t echoPin, uint8_t trigPin)
{
	uint8_t maximumRange = 200; // Maximum range needed
	uint8_t minimumRange = 0; // Minimum range needed
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
		return uint16_t(-1);
	}
	else {
		/* Send the distance to the computer using Serial protocol, and
		turn LED OFF to indicate successful reading. */
		return uint16_t(distance);
	}
}



sensor::~sensor()
{
	delete sensorEchoPin;
	delete sensorTrigPin;
	delete sensorDataEcho;
}

