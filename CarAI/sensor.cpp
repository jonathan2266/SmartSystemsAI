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
		for (size_t i = 0; i < 4; i++)
		{
			Serial.println(sensorDataEcho[i]);
		}
	}

}

uint8_t sensor::GetSensorData(uint8_t number)
{
	return uint8_t(sensorDataEcho[number]);
}

int sensor::echo(uint8_t echoPin, uint8_t trigPin)
{
	uint8_t maximumRange = 200; // Maximum range needed
	uint8_t minimumRange = 0; // Minimum range needed
	int duration, distance; // Duration used to calculate distance

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
		return int(-1);
	}
	else {
		/* Send the distance to the computer using Serial protocol, and
		turn LED OFF to indicate successful reading. */
		Serial.println(distance);
		return int(distance);
	}
}



sensor::~sensor()
{
	delete sensorEchoPin;
	delete sensorTrigPin;
	delete sensorDataEcho;
}

