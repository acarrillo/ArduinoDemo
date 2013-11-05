#include <Servo.h>

Servo myservo;
// Constants
int LLIM = 190;
int HLIM = 160;
int MID = 170;

int servoPos = MID;
int leftSense, midSense, rightSense;
int cmd = 0;

int servoPin = 3;
int motorPin = 4;
int leftSensePin = A0;
int midSensePin = A1;
int rightSensePin = A2;


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
  readSerial();
  doMotors();
}

void readSensors() {
    leftSense = digitalRead(leftSensePin);
    midSense = digitalRead(midSensePin);
    rightSense = digitalRead(rightSensePin);

    if (midSense && rightSense && !leftSense) { // Turn right
        servoPos = HLIM;

    }


}

void readSerial() {
  if (Serial.available() > 0){
    cmd = Serial.read();
    Serial.println(cmd);
    switch(cmd){
      case 49://LEFT
        servoPos = LLIM;
        break;
      case 50://RIGHT
        servoPos = HLIM;
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
