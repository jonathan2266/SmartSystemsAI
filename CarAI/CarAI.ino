#include "motor.h"
#include "sensor.h"
#include "ai.h"
#include "Arduino.h"
#include "sam.h"

ai robot;


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

	Serial.begin(9600);
	robot.setup();

}

// the loop function runs over and over again until power down or reset
void loop() {
	//test

	robot.start();

}
