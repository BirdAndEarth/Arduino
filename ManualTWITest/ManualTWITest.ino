#include <avr/io.h>
#include <util/delay.h>
#include "dv32u.h"

uint8_t data1;
uint8_t data2;
int data;
float temp;

void setup()
{
  Serial.begin(115200);
  delay(5);
  I2C_init();
  delay(5);
}


void loop()
{

  I2C_start();
//  delayMicroseconds(100);
  I2C_write(B10010000);
//  delayMicroseconds(100);
  I2C_write(B00000000);
//  delayMicroseconds(100);
  I2C_start();
//  delayMicroseconds(100);
  I2C_write(B10010001);
//  delayMicroseconds(100);
  data1 = I2C_read(1);
//  delayMicroseconds(100);
  data2 = I2C_read(0);
//  delayMicroseconds(100);
  I2C_stop();

data = data1 << 8;
data = (data + data2) >> 4;
temp = data * 0.0625;

delay(100);

Serial.println(temp);


/*
Serial.print(data1,BIN);
Serial.print(" ");
Serial.print(data2,BIN);
Serial.println("");
*/

}



