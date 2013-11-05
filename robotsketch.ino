#include <Servo.h>

Servo myservo;
int servoPos = 10;
int cmd = 0;
void setup() {
  Serial.begin(9600);
  myservo.attach(3);
}

void loop() {
  if (Serial.available() > 0){
    cmd = Serial.read();
    Serial.println(cmd);
    switch(cmd){
      case 49://LEFT 
        servoPos = 10;
        break;
      case 50://RIGHT
        servoPos = 170;
        break;
      case 51: //STRAIGHT
        servoPos = 90;
        break;
      case 52: //STOP
        Serial.println("bep");
        break;
        //Stop behavior
    }
  }
  myservo.write(servoPos);
}

