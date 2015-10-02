
#include <Wire.h>

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(12,OUTPUT);
}

void loop()
{
  int time;
  while(1){
    time = millis();
    if(time % 1000 == 0){
      digitalWrite(13,HIGH);
     
  byte b0, b1
  Wire.beginTransmission(96);
 // b0 = (dec >> 8) | 0x0F; 
 // b1 = dec & 0xFF
      Wire.send(b0);
      Wire.send(b1); // Needed twice, since the 4 lowest bits (of 12) are in the fourth byte
      Wire.endTransmission();
      digitalWrite(13,LOW);
    }
  }
}

int Da(int dec)
{
}





