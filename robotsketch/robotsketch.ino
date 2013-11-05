#include <Servo.h>

Servo myservo;
// Constants
int LLIM = 20;
int HLIM = 160;
int MID = 90;

int servoPos = MID;
int cmd = 0;
int servoPin = 3;
int motorPin = 4;
int motorState = LOW;

void setup() {
  Serial.begin(9600);

  myservo.attach(servoPin);
  pinMode(motorPin,OUTPUT);
}

void loop() {
  readSerial();
  doMotors();
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
