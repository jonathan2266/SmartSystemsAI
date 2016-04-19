/*
 Name:		CarAI.ino
 Created:	4/19/2016 2:02:54 PM
 Author:	jonathan
*/

const prog_uint8_t OrDDRD[1][8] = { 0,1,0,1,0,1,1,0 };
const prog_uint8_t OrDDRB[1][8] = { 0,0,0,0,0,0,0,0 };

int sensorDataEcho[4] = { -1,-1,-1,-1 }; //containers for holding the sensor value
int sensorEchoPin[4]; //hardcode these pins
int sensorTrigPin[4]; //hardcode these pins

int currentMotion; //the current movement the car is doing;
#define FOREWARD 1
#define STOP 2
#define BACKWARDS 3
#define LEFT 4
#define RIGHT 5

//defining sensors numbers and location in array
#define SENFL 0
#define SENFH 1
#define SENL 2
#define SENR 3

int carSpeed = 0; //with modulation we control the speed of the car

// the setup function runs once when you press reset or power the board
void setup() {
	
	//set DDRD(0-7) to select input and output pins 0 = input 1 = output
	DDRD = B01010110;

	//set DDRB(8-13) to select input and output pins
	//DDRB  = B nog niet veranderen zie ppt slide 4 audio-signaalbewerking

	fillSensors(5);

	//fill in currentmotion
	currentMotion = STOP;
}

// the loop function runs over and over again until power down or reset
void loop() {
  
	interpret_data(); 

	movement(); 

	fillSensors(5); //check all sensors

}

void fillSensors(int code) {

	if (code == 5)
	{
		for (int i = 0; i < sizeof(sensorDataEcho)/sizeof(sensorDataEcho[0]); i++)
		{
			sensorDataEcho[i] = echo(sensorEchoPin[i],sensorTrigPin[i]);
		}
	}
	else
	{
			sensorDataEcho[code] = echo(sensorEchoPin[code], sensorTrigPin[code]);
	}

}

int echo(int echoPin, int trigPin) {

	//pinMode(trigPin, OUTPUT);  //<-- should already have happened at the start of program
	//pinMode(echoPin, INPUT);

	int maximumRange = 200; // Maximum range needed
	int minimumRange = 0; // Minimum range needed
	long duration, distance; // Duration used to calculate distance
	/* The following trigPin/echoPin cycle is used to determine the
	distance of the nearest object by bouncing soundwaves off of it. */
	digitalWrite(trigPin, LOW); //fix digitalwrite should be replace.
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
		return(-1);
	}
	else {
		/* Send the distance to the computer using Serial protocol, and
		turn LED OFF to indicate successful reading. */
		return(distance);
	}

}

void interpret_data() {
	//some thoughts
	//keep a history of sensor data. if a sudden if a sudden value goes to -1 panick(a stop) depending on the current moveset thats being performed
	//
#define CLOSEDISTANCE 10;
	
	if (currentMotion == STOP)
	{
		//geef voorkeur aan FOREWARD

	}
	else if (currentMotion == FOREWARD)
	{
		//geef voorkeur aan de huidige motion
	}
	else if(currentMotion == BACKWARDS)
	{

	}
	else if (currentMotion == LEFT)
	{

	}
	else if (currentMotion == RIGHT)
	{

	}
	else
	{
		currentMotion = STOP;
	}


}

void movement() {

}