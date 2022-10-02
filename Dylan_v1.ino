/*
  ELEC1100 Project Code V1

  To program the car tracking the white line on a dark mat

  Your Name: TSANG YU

*/

// assign meaningful names to those pins that will be used

#define pinLeftSensor A5      //pin A5
#define pinBumperSensor A4    //pin A4
#define pinRightSensor A3     //pin A3

#define pinLdir 11            //pin D11
#define pinRdir 12            //pin D12

#define pinPWM_L 10           //pin D10
#define pinPWM_R 9            //pin D9

//define variables to be used in script

int leftSensor = 1;		  // not sensing white
int bumperSensor = 1;		  // not sensing white
int rightSensor = 1;		  // not sensing white

int countBumper = 0;		  // bumper not triggered yet

int countY = 0;

// the setup function runs once when you press reset or power the board

void setup ()
{
  // define pins as input and output
  pinMode(pinLeftSensor, INPUT);
  pinMode(pinRightSensor, INPUT);
  pinMode(pinBumperSensor, INPUT);

  pinMode(pinLdir, OUTPUT);
  pinMode(pinRdir, OUTPUT);

  pinMode(pinPWM_L, OUTPUT);
  pinMode(pinPWM_R, OUTPUT);

  // initialize output pins
  digitalWrite(pinLdir, HIGH);   //forward direction
  digitalWrite(pinRdir, HIGH);   //forward direction
  analogWrite(pinPWM_L, 0);      //stop at the start position
  analogWrite(pinPWM_R, 0);      //stop at the start position
}

// the loop function runs over and over again forever

void loop() {
  bumperSensor = digitalRead(pinBumperSensor);
  leftSensor = digitalRead(pinLeftSensor);
  rightSensor = digitalRead(pinRightSensor);

  // Car is reset at the start position
  if ( bumperSensor && countBumper == 0 ) {
    analogWrite(pinPWM_L, 0);
    analogWrite(pinPWM_R, 0);
  }

  // Bumper Sensor is triggered at the start position
  else if ( !bumperSensor && countBumper == 0) {
    analogWrite(pinPWM_L, 200);
    analogWrite(pinPWM_R, 200);
    countBumper = countBumper + 1;
    delay(350);     //to let car leave the start position to avoid sensors miscount 00 at the start position
  }

  // Car is tracking on the white line
  else if ( bumperSensor && countBumper == 1) {

    if ( !leftSensor && !rightSensor ) {
      turnSplit();
      countY += 1;
    }

    if ( !leftSensor && rightSensor ) {
      turnLeft();
    }

    if ( leftSensor && !rightSensor ) {
      turnRight();
    }

    if ( leftSensor && rightSensor ) {
      forWard();
    }
  }


  // bumper sensor sense the white wall
  else if ( !bumperSensor && countBumper == 1) {
    countBumper = countBumper + 1;
    backWard();
  }

  // backward and stop at the corner
  else if ( bumperSensor && countBumper == 2) {
    backWard();
    if (!leftSensor || !rightSensor) { // stop
      stop();
      countBumper = countBumper + 1;
    }
  }

}

void forWard() {
  if (countY >= 2) {
    analogWrite(pinPWM_L, 120);
    analogWrite(pinPWM_R, 120);
  }
  else {
    analogWrite(pinPWM_L, 200);
    analogWrite(pinPWM_R, 200);
  }
  digitalWrite(pinLdir, HIGH);
  digitalWrite(pinRdir, HIGH);
}


void turnLeft() {
  if (countY >= 2) {
    analogWrite(pinPWM_L, 50);
    analogWrite(pinPWM_R, 120);
  }
  else {
    analogWrite(pinPWM_L, 120);
    analogWrite(pinPWM_R, 200);
  }
  digitalWrite(pinLdir, LOW);
  digitalWrite(pinRdir, HIGH);
}

void turnSplit() {
  analogWrite(pinPWM_L, 120);
  analogWrite(pinPWM_R, 200);
  digitalWrite(pinLdir, LOW);
  digitalWrite(pinRdir, HIGH);
}

void turnRight() {
  if (countY >= 2) {
    analogWrite(pinPWM_L, 120);
    analogWrite(pinPWM_R, 50);
  }
  else {
    analogWrite(pinPWM_L, 200);
    analogWrite(pinPWM_R, 120);
  }
  digitalWrite(pinLdir, HIGH);
  digitalWrite(pinRdir, LOW);
}

void backWard() {
  analogWrite(pinPWM_L, 120);
  analogWrite(pinPWM_R, 120);
  digitalWrite(pinLdir, LOW);
  digitalWrite(pinRdir, LOW);
}

void stop() {
  analogWrite(pinPWM_L, 0);
  analogWrite(pinPWM_R, 0);
}
