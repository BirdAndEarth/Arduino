/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 12;
boolean flg = 0;
unsigned int time = 0;
unsigned int timeOld = 0;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  
  for(int i = 0; i < 24; i++){
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delayMicroseconds(5);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delayMicroseconds(10);
  // wait for a second
  }
  
  delay(100);


}
