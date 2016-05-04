#include "ai.h"


//setup sensors
uint16_t sensorEchoPin[4] = { 8,3,4,5 }; //these contain the pins for all the sensors
uint16_t sensorTrigPin[4] = { 9,3,3,3 };

sensor sensors(sensorEchoPin, sensorTrigPin); //giving them to the class

//setup engine
motor engine(6, 5, 10, 11);

ai::ai()
{

}

void ai::setup() {

	engine.setup();
	engine.LeftMotor(0, engine.FORWARD);
	engine.RightMotor(0, engine.FORWARD);
}

void ai::start() {

	
	engine.LeftMotor(255, engine.FORWARD);
	engine.RightMotor(255, engine.FORWARD);
	while (true)
	{
		sensors.fillSensors(sensors.SenF);
		if (sensors.GetSensorData(0) < 20)
		{
			engine.LeftMotor(0, engine.FORWARD);
			engine.RightMotor(0, engine.FORWARD);
		}
	}


}

ai::~ai()
{
}
