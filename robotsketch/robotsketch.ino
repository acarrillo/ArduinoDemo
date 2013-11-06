#include <Servo.h>

Servo myservo;
// Constants
int LEFT = 120;
int RIGHT = 60;
int MID = 90;

int servoPos = MID;
int leftSense, midSense, rightSense;
int cmd = 0;

int servoPin = 3;
int motorPin = 4;
int leftSensePin = 9;
int midSensePin = 10;
int rightSensePin = 8;


int motorState = LOW;

void setup() {
  Serial.begin(9600);

  myservo.attach(servoPin);
  pinMode(motorPin,OUTPUT);
  pinMode(leftSensePin,INPUT);
  pinMode(midSensePin,INPUT);
  pinMode(rightSensePin,INPUT);

  leftSense = midSense = rightSense = 0;
}

void loop() {
  //readSerial();
 readSensors();
  doMotors();
}

void readSensors() {
    leftSense = digitalRead(leftSensePin);
    midSense = digitalRead(midSensePin);
    rightSense = digitalRead(rightSensePin);

    Serial.print(leftSense);
    Serial.print("\t");
    Serial.print(midSense);
    Serial.print("\t");
    Serial.println(rightSense);
    
    motorState=HIGH;

    if (midSense && rightSense && !leftSense) { // Turn right
        servoPos = LEFT;
    }
    else if (midSense && leftSense && !rightSense) { // Turn left
        servoPos = RIGHT;
    }
    else if (midSense) {
        servoPos=MID;
    }
    else {
        //Keep last state
    }
}

void readSerial() {
  if (Serial.available() > 0){
    cmd = Serial.read();
    Serial.println(cmd);
    switch(cmd){
      case 49://LEFT
        servoPos = LEFT;
        break;
      case 50://RIGHT
        servoPos = RIGHT;
        break;
      case 51: //STRAIGHT
        servoPos = MID;
        break;
      case 52: //STOP
        motorState = LOW;
        break;
        case 53: //START
        motorState = HIGH;
        break;
    }
  }
}

void doMotors() {
  myservo.write(servoPos);
  digitalWrite(motorPin,motorState);
}
