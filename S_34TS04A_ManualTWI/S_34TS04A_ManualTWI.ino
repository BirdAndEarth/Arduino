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

int relayPin = PC6;
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

  int nt = 0;
  int t = 0;
  int ofs = 0;
  float ta = 34.0;
  uint8_t ofsbit = 0;



if (in == 10){
  TsWrite(0x00);
  delay(1000);
  nt = TsRead();
  ofsbit = nt - (int)(ta / 0.0625 + 0.5);

 TsWrite(ofsbit);

  

  Serial.print("in = ");
  Serial.println(in);

  Serial.print("nt = ");
  Serial.println(nt);
  
  Serial.print("ta = ");
  Serial.println((int)(ta / 0.0625 + 0.5));

  Serial.print("ofsbit = ");
  Serial.println(ofsbit);
  in = 0;
  }
  
  Serial.print("t =  ");
  Serial.println(TsRead()*0.0625);

  delay(1000);
  Serial.println("");
  in++;

}

// --Read and Write S-34TS04A ----------------------------
void TsWrite(uint8_t ofsbit)
{
  PowerOn();
  delay(10);

  // TS ShutDownMode Set
  I2C_start();
  I2C_write(B00110000);
  I2C_write(0x01);
  I2C_write(0x01);
  I2C_write(0x00);
  I2C_stop();

  // Test Enable set
  I2C_start_testmode();
  I2C_write_testmode(B01010101);
  I2C_start_testmode();
  I2C_write_testmode(B11101010);
  I2C_start_testmode();
  I2C_write(B01001010);
  I2C_write(B00001111);
  I2C_write(ofsbit);
  I2C_stop();


  delay(10);

  PowerOff();

  delay(300);
}

int TsRead()
{

  uint8_t data1 = 0;
  uint8_t data2 = 0;
  unsigned int data = 0;


  PowerOn();

  delay(10);

  // TS Shut Down Mode Set
  I2C_start();
  I2C_write(B00110000);
  I2C_write(B00000001);
  I2C_write(B00000001);
  I2C_write(B00000000);
  I2C_stop();

  // Resolution
  I2C_start();
  I2C_write(B00110000);
  I2C_write(B00001000);
  I2C_write(B00000000);
  I2C_write(B00000011);
  I2C_stop();

  // TS ShutDownModeRelease
  I2C_start();
  I2C_write(B00110000);
  I2C_write(B00000001);
  I2C_write(B00000000);
  I2C_write(B00000000);
  I2C_stop();

  delay(300);

  // Ambient Temperature Read
  I2C_start();
  I2C_write(B00110000); // Address + 0
  I2C_write(B00000101); // Register 0x85
  I2C_start();
  I2C_write(B00110001); // Address + 1
  data1 = I2C_read(ACK);
  data2 = I2C_read(NACK);
  I2C_stop();

  data1 = data1 & B1111;
  data = (data1 << 8) + data2;

  return data;

}

void PowerOn()
{
  digitalWrite(relayPin, HIGH);
}
void PowerOff()
{
  digitalWrite(relayPin, LOW);
}


