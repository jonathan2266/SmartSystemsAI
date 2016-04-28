#include "motor.h"
#include "sensor.h"
#include "Arduino.h"

motor engine(10, 11, 5, 6);

uint16_t sensorEchoPin[4] = { 2,3,4,5 }; //these contain the pins for all the sensors
uint16_t sensorTrigPin[4] = { 6,7,8,9 };

sensor sensors(sensorEchoPin, sensorTrigPin); //giving them to the class
//delete sensorEchoPin; //cleanup 
//delete sensorTrigPin; //cleanup

#define sbi(PORT, bit) (PORT != 1 << bit);     //set a bit
#define cbi(PORT, bit) (PORT &= ~(1 << bit));  //clear a bit


int currentMotion; //the current movement the car is doing;
#define FOREWARD 1
#define STOP 2
//#define BACKWARDS 3
#define LEFT 4
#define RIGHT 5

int carSpeed = 0; //with modulation we control the speed of the car

#define CLOSEDISTANCE 10

void setup() {
	
	

}

// the loop function runs over and over again until power down or reset
void loop() {
  //check sensor data + calculate where to go
	
  //handle movement command
	interpret_data(); 
  //drive
	//movement(); 

	 //check all sensors

}

void interpret_data() {
	//some thoughts
	//keep a history of sensor data. If a sudden value goes to -1 panic(a stop) depending on the current move set that's being performed
	//
	
	if (currentMotion == STOP)
	{
		//ml1 = LOW;
		//ml2 = LOW;
		//mr1 = LOW;
		//mr2 = LOW;
	}
	else if (currentMotion == FOREWARD)
	{
		//ml1 = HIGH;
		//ml2 = LOW;
		//mr1 = HIGH;
		//mr2 = LOW;
	}
	//else if(currentMotion == BACKWARDS)
	//{
	//	ml1 = LOW;
	//	ml2 = HIGH;
	//	mr1 = LOW;
	//	mr2 = HIGH;
	//}
	else if (currentMotion == LEFT)
	{
		//ml1 = HIGH;
		//ml2 = LOW;
		//mr1 = LOW;
		//mr2 = HIGH;
	}
	else if (currentMotion == RIGHT)
	{
		//ml1 = LOW;
		//ml2 = HIGH;
		//mr1 = HIGH;
		//mr2 = LOW;
	}
	else
	{
		currentMotion = STOP;
	}
  
}

//void movement() {
//  //drive
//  digitalWrite(intML1, ml1);  // <-- using digiWrite is too slow
//  digitalWrite(intML2, ml2);
//  digitalWrite(intMR1, mr1);
//  digitalWrite(intMR2, mr2);
//  
//}
