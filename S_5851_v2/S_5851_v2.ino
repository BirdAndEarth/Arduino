#include <Wire.h>
#include "dv32u.h"

#define S5851_ADDR 0x48

int LED = PC7;

// unsigned char i = 0;
int ret = 0;
int intTemp = 0;
int StoredData = 0;
float temp = 0;

void setup()
{
  pinMode(LED,OUTPUT);

  digitalWrite(LED,LOW);  
  Wire.begin();  
  Serial.begin(115200);
  Serial1.begin(115200);

  delay(100);
  //  nameString = "--------";
}

void loop()
{ 
  tempRead();
  Serial.println(temp);
  Serial1.println(temp);
  
  delay(100);

}
// S-5851  ////////////////////////////////////////////////////
void tempRead()
{
  int data1=0;
  int data2=0;
  int data=0;
  temp = 0;

  //Dummy Write
  Wire.beginTransmission(S5851_ADDR);
  Wire.write(0x00);

  //Read Data 
  ret=Wire.requestFrom(S5851_ADDR, 2);
  if (Wire.available()) {
    data1 = Wire.read();
    data2 = Wire.read();

    data1= data1 << 8;
    data = data1 + data2;
    data = data >> 4;
    temp = data*0.0625;

    //data = temp * 10;

    StoredData = data;
    intTemp = data;    
  } 
  else {
    intTemp=999; 
  }
  ret=Wire.endTransmission();
}


// -------END of CODE--------------------------------------
