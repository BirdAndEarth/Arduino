
#include <I2C.h>
#include "dv32u.h"


#define S5851_ADDR 0x48

int LED = 13;

// unsigned char i = 0;
int ret;
int intTemp = 0;
int StoredData = 0;
float temp = 0;


/*
  74HC4066
  1Z TEST SDA
  2Z TEST SCL
  3Z SCL
  4Z SDA
*/



int TEST_SCL = PD2;
int TEST_SDA = PD3;
int SA1 = PD4;
int SW_I2C = PD6;
int SW_TEST = PD7;

void setup()
{
  pinMode(LED,OUTPUT);

  pinMode(TEST_SCL, OUTPUT);
  pinMode(TEST_SDA, OUTPUT);
  pinMode(SA1, OUTPUT);
  pinMode(SW_I2C, OUTPUT);
  pinMode(SW_TEST, OUTPUT);

  digitalWrite(TEST_SCL, HIGH);
  digitalWrite(TEST_SDA, HIGH);
  digitalWrite(SA1, LOW);
  digitalWrite(SW_I2C, HIGH);
  digitalWrite(SW_TEST, LOW);
  
  digitalWrite(LED,LOW);  
  Serial.begin(115200);
  I2c.begin();
  delay(50);
}

void loop()
{
  digitalWrite(LED,HIGH);
  tempRead();
    Serial.println(temp);
  delay(50);

  digitalWrite(LED,LOW);
  delay(450);



//  I2c.read(HMC5883L,0x00,2); //read 6 bytes (x,y,z) from the device
//  x = I2c.receive() << 8;
//  x |= I2c.receive();
}



void tempRead()
{
  int data1=0;
  int data2=0;
  int data=0;
  temp = 0;

  I2c.read(S5851_ADDR,0x00,2);
    data1 = I2c.receive();
    data2 = I2c.receive();

    data1= data1 << 8;
    data = data1 + data2;
    data = data >> 4;
    temp = data*0.0625;

    //data = temp * 10;

    StoredData = data;
    intTemp = data;    

}



