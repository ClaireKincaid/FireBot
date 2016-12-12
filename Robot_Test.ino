//Sketch to test motors on rover 5 chassis
//written by Claire Kincaid 11/10/2016

//include libraries
#include <Dagu4Motor.h>
#include <Encoder.h>

//wall sensors pin
int sensorFront = analogRead (A0);
int sensorLeft = analogRead (A1);
int sensorRight = analogRead (A2);
//int sensorBack = analogRead (A3);

//create motor object
int dirPin1 = 2;
int pwmPin1 = 3;
Dagu4Motor motor1 =  Dagu4Motor(pwmPin1, dirPin1, 0, 0, 0);
int dirPin2 = 4;
int pwmPin2 = 5;
Dagu4Motor motor2 =  Dagu4Motor(pwmPin2, dirPin2, 0, 0, 0);
int dirPin3 = 7;
int pwmPin3 = 6;
Dagu4Motor motor3 =  Dagu4Motor(pwmPin3, dirPin3, 0, 0, 0);
int dirPin4 = 8;
int pwmPin4 = 9;
Dagu4Motor motor4 =  Dagu4Motor(pwmPin4, dirPin4, 0, 0, 0);

void setup() {
  // put your setup code here, to run once:
  // the chassis is moving forward
motor1.setSpeed(100);
motor1.setMotorDirection(0);
motor1.begin();
motor2.setSpeed(100);
motor2.setMotorDirection(1);
motor2.begin();
motor3.setSpeed(100);
motor3.setMotorDirection(0);
motor3.begin();
motor4.setSpeed(100);
motor4.setMotorDirection(1);
motor4.begin();

}

void loop() {
  // put your main code here, to run repeatedly:




}
