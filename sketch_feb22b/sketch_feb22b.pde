#include <Wire.h>

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(13,OUTPUT);
  Serial.begin(115200);

}

int dec = 4095;
void loop()
{ 
  byte b0, b1;
  Wire.beginTransmission(96);
  b0 = (dec >> 8) & 0x0F; 
  b1 = dec & 0xFF;
  digitalWrite(13,HIGH);
  Wire.beginTransmission(96); // transmit to device #44 (0x2c)
  Wire.send(b0);
  Wire.send(b1); // Needed twice, since the 4 lowest bits (of 12) are in the fourth byte
  Wire.endTransmission();
  digitalWrite(13,LOW);
  Serial.print("dec = ");
  Serial.print(dec);
  Serial.print(" Read = ");
  Serial.println(analogRead(0));
  
  delay(500);
  dec = dec >> 1 ;
  if (dec == 0)
    dec = 4095;
}
