//include libraries
#include <Dagu4Motor.h>
#include <Encoder.h>
#include <i2cmaster.h>

//flame sensors pin
const int FlamesensorLeft = A0;
const int FlamesensorRight = A1;

//wall sensors pin
const int WallsensorLeft = A2;
const int WallsensorRight = A3;

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
  Serial.begin(9600);
  i2c_init(); //Initialise the i2c bus for the heat sensor
  PORTC = (1 << PORTC4) | (1 << PORTC5); //enable pullups
    // Room's Temperature Reference
  int dev = 0x5A << 1;
  int data_low = 0;
  int data_high = 0;
  int pec = 0;

  i2c_start_wait(dev + I2C_WRITE);
  i2c_write(0x07);

  // read
  i2c_rep_start(dev + I2C_READ);
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
  tempData = (tempData * tempFactor) - 0.01;

  float room_temp_celcius = tempData - 273.15;
}

void loop() {
  // 2 FLAME SENSORS
  FlameSensorValueRight = analogRead(FlamesensorRight);
  FlameSensorValueLeft = analogRead(FlamesensorLeft);

  difflame = FlameSensorValueLeft - FlameSensorValueRight;
  
  // 2 WALL SENSORS : 
  WallSensorValueLeft = analogRead(WallsensorLeft);
  WallSensorValueRight = analogRead(WallsensorRight);

  // HEAT SENSOR
  int dev = 0x5A << 1;
  int data_low = 0;
  int data_high = 0;
  int pec = 0;

  i2c_start_wait(dev + I2C_WRITE);
  i2c_write(0x07);

  // read
  i2c_rep_start(dev + I2C_READ);
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
  tempData = (tempData * tempFactor) - 0.01;

  float temp_celcius = tempData - 273.15;

  diftemp = temp_celcius - room_temp_celcius;

   

  if (WallSensorValueLeft>500) // there is a wall on the forward-left side of the bot, the bot has to go backward and turn to the right
  { 
    // the chassis is moving backward
motor1.setSpeed(100);
motor1.setMotorDirection(1);
motor1.begin();
motor2.setSpeed(100);
motor2.setMotorDirection(0);
motor2.begin();
motor3.setSpeed(100);
motor3.setMotorDirection(1);
motor3.begin();
motor4.setSpeed(100);
motor4.setMotorDirection(0);
motor4.begin();
delay (1000);

// the chassis is moving to the right
motor1.setSpeed(100);
motor1.setMotorDirection(0);
motor1.begin();
motor2.setSpeed(100);
motor2.setMotorDirection(1);
motor2.begin();
motor3.setSpeed(100);
motor3.setMotorDirection(1);
motor3.begin();
motor4.setSpeed(100);
motor4.setMotorDirection(0);
motor4.begin();
  }

  
  else if (WallSensorValueRight>500) // there is a wall on the forward-right side of the bot, the bot has to go backward aand turn to the left
{
  // the chassis is moving backward
motor1.setSpeed(100);
motor1.setMotorDirection(1);
motor1.begin();
motor2.setSpeed(100);
motor2.setMotorDirection(0);
motor2.begin();
motor3.setSpeed(100);
motor3.setMotorDirection(1);
motor3.begin();
motor4.setSpeed(100);
motor4.setMotorDirection(0);
motor4.begin();
delay (1000);

// the chassis is moving to the left
motor1.setSpeed(100);
motor1.setMotorDirection(1);
motor1.begin();
motor2.setSpeed(100);
motor2.setMotorDirection(0);
motor2.begin();
motor3.setSpeed(100);
motor3.setMotorDirection(0);
motor3.begin();
motor4.setSpeed(100);
motor4.setMotorDirection(1);
motor4.begin();
}


  else if (difflame>60) // the flame is on the left, the bos has to turn left
{
// the chassis is moving to the left
motor1.setSpeed(100);
motor1.setMotorDirection(1);
motor1.begin();
motor2.setSpeed(100);
motor2.setMotorDirection(0);
motor2.begin();
motor3.setSpeed(100);
motor3.setMotorDirection(0);
motor3.begin();
motor4.setSpeed(100);
motor4.setMotorDirection(1);
motor4.begin();
}


  else if (difflame<-60) // the flame is on the right, the bos has to turn right
{
// the chassis is moving to the right
motor1.setSpeed(100);
motor1.setMotorDirection(0);
motor1.begin();
motor2.setSpeed(100);
motor2.setMotorDirection(1);
motor2.begin();
motor3.setSpeed(100);
motor3.setMotorDirection(1);
motor3.begin();
motor4.setSpeed(100);
motor4.setMotorDirection(0);
motor4.begin();
}


  else if ((-60<difflame<60) && (WallSensorValueRight<500) && (WallSensorValueLeft<500) && (FlameSensorValueRight>50) && (FlameSensorValueLeft>50) ) // there is no wall but the flame is between the two flame sensors, slow down
  {
    // the chassis is moving forward slowly
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

  
  else if ((-60<difflame<60) && (WallSensorValueRight<500) && (WallSensorValueLeft<500) && (FlameSensorValueRight<50) && (FlameSensorValueLeft>50) ) // there is nothing in front of both sensors, the bot is going forward
  {
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


    else if ((-60<difflame<60) && (WallSensorValueRight<500) && (WallSensorValueLeft<500) && (FlameSensorValueRight>50) && (FlameSensorValueLeft>50) && (diftemp>5) ) //the bot is just in front of the flame, it stops and extinguishes it
    {
motor1.stopMotors();
motor2.stopMotors();
motor3.stopMotors();
motor4.stopMotors();      
    }

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

// the chassis is moving backward
motor1.setSpeed(100);
motor1.setMotorDirection(1);
motor1.begin();
motor2.setSpeed(100);
motor2.setMotorDirection(0);
motor2.begin();
motor3.setSpeed(100);
motor3.setMotorDirection(1);
motor3.begin();
motor4.setSpeed(100);
motor4.setMotorDirection(0);
motor4.begin();

// the chassis is moving to the right
motor1.setSpeed(100);
motor1.setMotorDirection(0);
motor1.begin();
motor2.setSpeed(100);
motor2.setMotorDirection(1);
motor2.begin();
motor3.setSpeed(100);
motor3.setMotorDirection(1);
motor3.begin();
motor4.setSpeed(100);
motor4.setMotorDirection(0);
motor4.begin();

// the chassis is moving to the left
motor1.setSpeed(100);
motor1.setMotorDirection(1);
motor1.begin();
motor2.setSpeed(100);
motor2.setMotorDirection(0);
motor2.begin();
motor3.setSpeed(100);
motor3.setMotorDirection(0);
motor3.begin();
motor4.setSpeed(100);
motor4.setMotorDirection(1);
motor4.begin();


}
