#include <Servo.h>
#include <Dagu4Motor.h>
#include <Encoder.h>

const int FlamesensorRight = A0;
int FlameSensorValueRight=0;

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


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
    Serial.begin(9600);
  myservo.attach(10); 
motor1.setSpeed(50);
motor1.setMotorDirection(0);
motor1.begin();
motor2.setSpeed(50);
motor2.setMotorDirection(1);
motor2.begin();
motor3.setSpeed(50);
motor3.setMotorDirection(0);
motor3.begin();
motor4.setSpeed(50);
motor4.setMotorDirection(1);
motor4.begin();
}

void loop() {
  FlameSensorValueRight = analogRead(FlamesensorRight);

  if (FlameSensorValueRight>975) {
    motor1.stopMotors();
    motor2.stopMotors();
    motor3.stopMotors();
    motor4.stopMotors();
    Serial.print("1"); 
        for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Serial.println(pos);
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  Serial.print("3");
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
}

