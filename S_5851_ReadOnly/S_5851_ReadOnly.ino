/*********************************************

S-34TS04A READ and WRITE

  PIN CONFIGURE
  
  SCL   PD0
  SDA   PD1
  SA1   PD2
  Relay PD3

*********************************************/
#include <avr/io.h>
#include <util/delay.h>
#include "dv32u.h"
#include "s34ts04a.h"

#define S5851_ADDR 0x48

#define R 1
#define W 0

#define ACK 1
#define NACK 0

int relayPin = PD3;
int in = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  //  pinMode(PD2, OUTPUT);
  delay(5);
  I2C_init();
  delay(5);
  digitalWrite(relayPin, LOW);
  //  digitalWrite(PD2, LOW);
}



void loop()
{

  Serial.print("t =  ");
  Serial.println(TsRead());

  delay(1000);
  Serial.println("");

}

// --Read and Write S-34TS04A ----------------------------
int TsRead()
{

  int da1 = 0;
  int da2 = 0;
  long da = 0;

  // Ambient Temperature Read
  I2C_start();
  I2C_write(B10010000); // Address + 0
  I2C_write(B00000000); // Register 0x85

  I2C_start();
  I2C_write(B10010001); // Address + 1
  da1 = I2C_read(ACK);
  da2 = I2C_read(NACK);
  I2C_stop();

  Serial.print("data1 = ");
  Serial.print(da1, BIN);
  Serial.print("\t data2 = ");
  Serial.print(da2, BIN);
  Serial.println("");



  da1 = da1 << 8;
  da2 = da1 + da2;
  da = da >> 4;
  
  
  return da;

}

void PowerOn()
{
  digitalWrite(relayPin, HIGH);
}
void PowerOff()
{
  digitalWrite(relayPin, LOW);
}


