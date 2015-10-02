#include <avr/io.h>
#include <util/delay.h>
#include "dv32u.h"

#define S5851_ADDR 0x48

#define R 1
#define W 0

#define ACK 1
#define NACK 0




void setup()
{
  Serial.begin(115200);
  delay(5);
  I2C_init();
  delay(5);
}


void loop()
{
  Serial.println(tempRead());
  delay(500);
}

// ---------------------------------------------------------------
float tempRead(void)
{
  uint8_t data1;
  uint8_t data2;
  int data;
  float temp;

  I2C_start();
  I2C_write(S5851_ADDR << 1 | W);
  I2C_write(B00000000);
  I2C_start();
  I2C_write(S5851_ADDR << 1 | R);
  data1 = I2C_read(ACK);
  data2 = I2C_read(NACK);
  I2C_stop();

  data = data1 << 8;
  data = (data + data2) >> 4;
  temp = data * 0.0625;
  return temp;
}


