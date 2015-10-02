#include <SoftwareSerial.h>

int led = 4;
int d = 100;

SoftwareSerial mySerial(2, 1); // RX, TX
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT); 
  mySerial.begin(1200);  
}

// the loop routine runs over and over again forever:
void loop() {
//  if (mySerial.available()) {
//      while(mySerial.available()){
//        mySerial.read();
//      }
    
    mySerial.println("Hello World!\t");
    
    digitalWrite(led, HIGH);
    delay(500);
     digitalWrite(led, LOW);
    delay(500);
  
}
