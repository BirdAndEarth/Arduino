// --------------------------------------------------------
// S-24CS02A Arduino read and write
//                                     2013/03/19 TheMaker
// --------------------------------------------------------

#include <Wire.h>

#define ADDR 0b1010000

void setup()
{
  Wire.begin();
  Serial.begin(115200);
}

void loop()
{
  byte bby = 0;


  for (int i = 0; i <= 255; i++){
    int adr = i;
    b = byte(i);
    eeWrite(adr, b);
    delay(10);
/*

    Serial.println("");
    Serial.print("write:\t");
    Serial.print("adr = ");
    Serial.print(adr,BIN);
    Serial.print(" value = ");
    Serial.println(b ,BIN);

    delay(10);
*/
    Serial.print("read:\t");
    Serial.print("adr = ");
    Serial.print(adr,BIN);
    Serial.print("\tvalue = ");
    Serial.println(eeRead(adr),BIN);
    delay(5);
  }

  delay(10000);


}



void eeWrite(int adr, byte value)
{
  Wire.beginTransmission(ADDR);
  Wire.write(byte(adr));  
  Wire.write(value);  
  Wire.endTransmission();
}

byte eeRead(int adr)
{
  byte by = 0;

  // Dummy Write
  Wire.beginTransmission(ADDR);
  Wire.write(byte(adr));
  Wire.endTransmission();

  // Read
  Wire.requestFrom(ADDR, 1);
  while(Wire.available())
  { 
    by = Wire.read();
  }
 
  return by;
}












