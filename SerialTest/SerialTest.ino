int inByte = 0;         // incoming serial byte

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(115200);
  while (!Serial) {
  }
  pinMode(13, OUTPUT);   // digital sensor is on digital pin 2
}


void loop()
{
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    char c = Serial.read();    
    if (c == 'f') { // nが送られてきたらLEDを点灯させる。
      digitalWrite(13, HIGH);
    } 
    else if(c == 'j') { // fが送られてきたらLEDを消灯させる。
      digitalWrite(13, LOW);
    }
  }
}



