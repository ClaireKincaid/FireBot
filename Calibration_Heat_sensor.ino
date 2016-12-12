#include <i2cmaster.h>

  int diftemp=0;

void setup() {
  Serial.begin(9600);
  i2c_init(); //Initialise the i2c bus for the heat sensor
  PORTC = (1 << PORTC4) | (1 << PORTC5); //enable pullups
    // Room's Temperature Reference
  int dev1 = 0x5A << 1;
  int data_low1 = 0;
  int data_high1 = 0;
  int pec1 = 0;

  i2c_start_wait(dev1 + I2C_WRITE);
  i2c_write(0x07);

  // read
  i2c_rep_start(dev1 + I2C_READ);
  data_low1 = i2c_readAck(); //Read 1 byte and then send ack
  data_high1 = i2c_readAck(); //Read 1 byte and then send ack
  pec1 = i2c_readNak();
  i2c_stop();

  //This converts high and low bytes together and processes temperature, MSB is a error bit and is ignored for temps
  double tempFactor1 = 0.02; // 0.02 degrees per LSB (measurement resolution of the MLX90614)
  double tempData1 = 0x0000; // zero out the data
  int frac1; // data past the decimal point

  // This masks off the error bit of the high byte, then moves it left 8 bits and adds the low byte.
  tempData1 = (double)(((data_high1 & 0x007F) << 8) + data_low1);
  tempData1 = (tempData1 * tempFactor1) - 0.01;

  float room_temp_celcius = tempData1 - 273.15;
}


void loop() {
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

  Serial.print("difference of temperature : ");
  Serial.println(diftemp);

      delay(500); // wait before printing again
}
