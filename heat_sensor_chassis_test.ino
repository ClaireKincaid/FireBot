//Sketch to test motors on rover 5 chassis
//written by Claire Kincaid 11/10/2016
 
//include libraries
#include <Dagu4Motor.h>
#include <Encoder.h>
#include <i2cmaster.h>
 
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
    motor1.setSpeed(75);
    motor1.setMotorDirection(0);
    motor2.setSpeed(75);
    motor2.setMotorDirection(1);
    motor3.setSpeed(75);
    motor3.setMotorDirection(0);
    motor4.setSpeed(75);
    motor4.setMotorDirection(1);
    
  Serial.begin(9600);
  Serial.println("Setup...");
  i2c_init(); //Initialise the i2c bus
  PORTC = (1 << PORTC4) | (1 << PORTC5);//enable pullups
 
}
 
void loop() {
  // put your main code here, to run repeatedly:
    int dev = 0x5A<<1;
    int data_low = 0;
    int data_high = 0;
    int pec = 0;
    int roomtemperature = 23.80;
   
    i2c_start_wait(dev+I2C_WRITE);
    i2c_write(0x07);
   
    // read
    i2c_rep_start(dev+I2C_READ);
    data_low = i2c_readAck(); //Read 1 byte and then send ack
    data_high = i2c_readAck(); //Read 1 byte and then send ack
    pec = i2c_readNak();
    i2c_stop();
   
    //This converts high and low bytes together and processes temperature, MSB is a error bit and is ignored for temps
    double tempFactor = 0.02; // 0.02 degrees per LSB (measurement resolution of the MLX90614)
    double tempData = 0x0000; // zero out the data
    int frac; // data past the decimal point
   
    // This masks off the error bit of the high byte, then moves it left 8 bits and adds the low byte.
    tempData = (double)(((data_high & 0x007F) << 8) + data_low);
    tempData = (tempData * tempFactor)-0.01;
   
    float celcius = tempData - 273.15;
 
    Serial.print("Celcius: ");
    Serial.println(celcius);
   
    motor1.begin();
    motor2.begin();
    motor3.begin();
    motor4.begin();
 
    if (celcius >= 25.50) {
      motor1.stopMotors();
      motor2.stopMotors();
      motor3.stopMotors();
      motor4.stopMotors();
    }
 
}
//20161115 it works.
