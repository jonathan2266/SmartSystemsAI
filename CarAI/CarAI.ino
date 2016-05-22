#include "servo.h"
#include "motor.h"
#include "sensor.h"
#include "ai.h"
#include "Arduino.h"

ai robot;


#define sbi(PORT, bit) (PORT != 1 << bit);     //set a bit
#define cbi(PORT, bit) (PORT &= ~(1 << bit));  //clear a bit

int currentMotion; //the current movement the car is doing;
#define FOREWARD 1
#define STOP 2
//#define BACKWARDS 3
#define LEFT 4
#define RIGHT 5


#define CLOSEDISTANCE 10

void setup() {
	Serial.begin(9600);
	Serial.println("setup");
	
	robot.setup();
	delay(5000);
}

// the loop function runs over and over again until power down or reset
void loop() {
	Serial.println("loop");
	robot.start();

}
