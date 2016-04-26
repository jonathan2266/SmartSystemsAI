//Pins motor
int intML1 = 6;     //Pin motor Left Front
int intML2 = 7;     //Pin motor Left Backwards
int intMLE = 10;    //Pin motor Left Enable
int intMR1 = 8;    //Pin Motor Right Front
int intMR2 = 9;    //Pin Motor Right Backwards
int intMRE = 11;     //Pin Motor Right Enable

//State motors;
uint8_t ml1 = LOW;    //Left motor 1  A1
uint8_t ml2 = LOW;    //Left motor 2  A2
uint8_t mr1 = LOW;    //Right motor 1 B1
uint8_t mr2 = LOW;    //Right motor 2 B2

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

#define CLOSEDISTANCE 10;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(intML1, OUTPUT);
  pinMode(intML2, OUTPUT);
  pinMode(intMR1, OUTPUT);
  pinMode(intMR2, OUTPUT);
  
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
  //check sensor data + calculate where to go
  echoFront(1, 2);
  echoSide(1, 2, 3, 4);
  //handle movement command
	interpret_data(); 
  //drive
	movement(); 

	fillSensors(5); //check all sensors

}

void fillSensors(int code) {
//echo has to be replaced by echoFront/echoSide
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

int echoFront(int echoPin, int trigPin) {
 
    //pinMode(trigPin, OUTPUT);  //<-- should already have happened at the start of program
    //pinMode(echoPin, INPUT);
 
    //int maximumRange = 200; // Maximum range needed
    int minimumRange = 20; // Minimum range needed
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
 
    if (distance <= minimumRange) {
    //Front sensor encountered wall or car
        return(-1);
    int direction = echoSide(1, 2, 3, 4); //actual pins will be different
    if (direction == 1) {
      //Turn Left
      currentMotion = LEFT;
      }
    if (direction == 2) {
      //Turn Right  
      currentMotion = RIGHT;
        }
    }
    else {
        return(distance);
     //Go Straight
     currentMotion = FORWARD;
    }
}
 
int echoSide(int echoPinLeft, int echoPinRight, int trigPinLeft, int trigPinRight) {
  // This method is to determine whether to turn left or right
  // when an object is detected in method echoFront
  long distanceLeft, distanceRight, durationLeft, durationRight;
 
  digitalWrite(trigPinLeft, LOW);
  digitalWrite(trigPinRight, LOW);
  delayMicroseconds(2);
 
  digitalWrite(trigPinLeft, HIGH);
  digitalWrite(trigPinRight, HIGH);
  delayMicroseconds(10);
 
  digitalWrite(trigPinLeft, LOW);
  digitalWrite(trigPinRight, LOW);
 
  durationLeft = pulseIn(echoPinLeft, HIGH);
  durationRight = pulseIn(echoPinRight, HIGH);
 
  //Calculate the distance (in cm) based on the speed of sound.
  distanceLeft = durationLeft / 58.2;
  distanceRight = durationRight / 58.2;
 
  if (distanceLeft > CLOSEDISTANCE && distanceRight > CLOSEDISTANCE) {
      if (distanceLeft > distanceRight) {
      //More space to the left so go left
      //return left
      return(1);
      }
    else if (distanceLeft < distanceRight) {
      //More space to the right so go right
      //return right
      return(2);
      }  
    else {
      //return right
      return(2);
      }    
    }
  else if (distanceLeft <= CLOSEDISTANCE){
      //Object spotted close to left sensor
      //Turn Right
      currentMotion = RIGHT;
    }  
  else if (distanceRight <= CLOSEDISTANCE) {
     //Object spotted close to right sensor
     //Turn Left
     currentMotion = LEFT;
    }
  else {
     currentMotion = STOP;
    }  
}

void interpret_data() {
	//some thoughts
	//keep a history of sensor data. If a sudden value goes to -1 panic(a stop) depending on the current move set that's being performed
	//
	
	if (currentMotion == STOP)
	{
		ml1 = LOW;
    ml2 = LOW;
    mr1 = LOW;
    mr2 = LOW;
	}
	else if (currentMotion == FOREWARD)
	{
		ml1 = HIGH;
    ml2 = LOW;
    mr1 = HIGH;
    mr2 = LOW;
	}
	else if(currentMotion == BACKWARDS)
	{
    ml1 = LOW;
    ml2 = HIGH;
    mr1 = LOW;
    mr2 = HIGH;
	}
	else if (currentMotion == LEFT)
	{
    ml1 = HIGH;
    ml2 = LOW;
    mr1 = LOW;
    mr2 = HIGH;
	}
	else if (currentMotion == RIGHT)
	{
    ml1 = LOW;
    ml2 = HIGH;
    mr1 = HIGH;
    mr2 = LOW;
	}
	else
	{
		currentMotion = STOP;
	}
  
}

void movement() {
  //drive
  digitalWrite(intML1, ml1);
  digitalWrite(intML2, ml2);
  digitalWrite(intMR1, mr1);
  digitalWrite(intMR2, mr2);
  
}
