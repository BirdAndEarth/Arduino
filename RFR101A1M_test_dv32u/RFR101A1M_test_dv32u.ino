#include "dv32u.h"


int flg = 0;
String id = "";
char buf;



void setup()
{
  Serial1.begin(9600);
  Serial.begin(115200);
  
  pinMode(13, OUTPUT);
  
  

}
void loop()
{
  if(Serial1.available())
  {
    while(Serial1.available()) {
      buf = Serial1.read();

      switch (buf) {
      case 0x02:
        flg = 1;
        digitalWrite(13, HIGH);
        break;

      case 0x03:
        digitalWrite(13, LOW);

        flg = 0;
        Serial.println(id);
        id = "";

        break;

      default:
        id += buf;
      }
    }
  }
}


