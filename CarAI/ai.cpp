#include "ai.h"

#define SENSORCOUNT 3 //also change in sensors.cpp
#define MINWHILEDELAY delay(60);

//setup sensors
uint16_t sensorEchoPin[4] = { 2,13,4,8}; //these contain the pins for all the sensors
uint16_t sensorTrigPin[4] = { 47,51,49,8}; //9

uint32_t snapshot;

sensor sensors(sensorEchoPin, sensorTrigPin); //giving them to the class

uint8_t leftWarningCount = 0;
uint32_t leftWallHangingTime;

//setup engine
motor engine(6, 5, 10, 11);
//setup servo
servoCar servo(7);

bool servoDotted = false;

void ai::setup() {

	engine.setup();
	engineStop();

	//servo.line(servoDotted);

	sensors.fillSensors(5);
	for (size_t i = 0; i < SENSORCOUNT; i++)
	{
		sensorData[i] = sensors.GetSensorData(i); //maybe
	}

	leftWallHangingTime = millis();
}

void ai::start() {

	engineForward(255);
	
	snapshot = millis();
	
	while (true)
	{
		checkSurroundings(0);
		delay(20);
		if (millis() - snapshot >= 5500)
		{
			Serial.println("startLeftCircle");
			startLeftCircle();
			break;
		}
	}

	snapshot = millis();

	while (true)
	{
		checkSurroundings(1);
		delay(20);
		if (millis() - snapshot >= 27000)
		{
			break;
		}
	}

}

void ai::checkSurroundings(uint8_t mode) { //mode 0 straight mode 1 circle
	
	Serial.println("entering checksurroundings");
	sensors.fillSensors(5);

	if (sensors.GetSensorData(sensors.SenF) < 12 && sensors.GetSensorData(sensors.SenL) < 12 && sensors.GetSensorData(sensors.SenR) < 12)
	{
		Serial.println("lele");
		engineStop();
		mode = 3;
	}

	//servo.line(servoDotted);

	if (mode == 0 || mode == 1)
	{
		for (size_t i = 0; i < SENSORCOUNT; i++)
		{

			// add function to check all sensors to see if the car is not locked in position

			if (sensors.GetSensorData(i) < 12)
			{
				engineStop();

				if (i == sensors.SenF)
				{
					Serial.println("SenF warning");
					//turn left or right
					if (sensors.GetSensorData(sensors.SenL) - sensors.GetSensorData(sensors.SenR) <= 0)
					{
						spinRight(200);
						//turn right
						while (true)
						{
							sensors.fillSensors(sensors.SenF);
							Serial.println(sensors.GetSensorData(sensors.SenF));
							if (sensors.GetSensorData(sensors.SenF) >= 100)
							{
								carBackOnRail(mode);
								break;
							}
							MINWHILEDELAY
						}
					}
					else
					{
						spinLeft(200);
						while (true)
						{
							//turn left
							sensors.fillSensors(sensors.SenF);
							Serial.println(sensors.GetSensorData(sensors.SenF));
							Serial.println("wut");
							if (sensors.GetSensorData(sensors.SenF) >= 100)
							{

								carBackOnRail(mode);
								break;
							}
							MINWHILEDELAY
						}
					}
				}
				else if(i == sensors.SenL)
				{
					Serial.println("senL warning");  // if sensor left ois triggered 5 times in x amount of time do a 180 + degree turn to run away from the wall
					avoidLeftWallhanging();
					//turn right
					while (true)
					{
						spinRight(200);
						sensors.fillSensors(5);
						if (sensors.GetSensorData(sensors.SenF) >= 100 && sensors.GetSensorData(sensors.SenL) >= 12) //and sensors.getsensorsdate(sensors.senL) >= 15
						{
							carBackOnRail(mode);
							break;
						}
						MINWHILEDELAY
					}
				}
				else if(i == sensors.SenR)
				{
					Serial.println("senR warning");
					//turn left
					while (true)
					{
						spinLeft(200);
						sensors.fillSensors(5);
						if (sensors.GetSensorData(sensors.SenF) >= 100 && sensors.GetSensorData(sensors.SenR) >= 12) //and sensors.getsensorsdate(sensors.senR) >= 15
						{
							carBackOnRail(mode);
							break;
						}
						MINWHILEDELAY
					}

				}
			}
			//servoDotted = !servoDotted;
		}
	}
}

void ai::carBackOnRail(uint8_t mode) {

	if (mode == 0)
	{
		engineForward(255);
	}
	else if (mode == 1)
	{
		startLeftCircle();
	}

}

void ai::avoidLeftWallhanging()
{
	leftWarningCount++;
	if (leftWarningCount > 5)
	{
		if (millis() - leftWallHangingTime < 7000)
		{
			spinRight(255);
			delay(3500);
		}
		else
		{
			leftWarningCount = 0;
			leftWallHangingTime = millis();
		}
	}
}

void ai::startLeftCircle() {
	engine.LeftMotor(200, engine.FORWARD);
	engine.RightMotor(255, engine.FORWARD);
}

void ai::engineStop() {
	engine.LeftMotor(0, engine.FORWARD);
	engine.RightMotor(0, engine.FORWARD);
}

void ai::spinLeft(uint8_t speed) {
	engine.RightMotor(speed, engine.FORWARD);
	engine.LeftMotor(speed, engine.BACKWARDS);
}

void ai::spinRight(uint8_t speed) {
	engine.LeftMotor(250, engine.FORWARD);
	engine.RightMotor(speed, engine.BACKWARDS);
}

void ai::engineForward(uint8_t speed) {
	engine.LeftMotor(speed, engine.FORWARD);
	engine.RightMotor(speed, engine.FORWARD);
}
ai::~ai()
{
	delete sensorEchoPin;
	delete sensorData;
	delete sensorTrigPin;
}
