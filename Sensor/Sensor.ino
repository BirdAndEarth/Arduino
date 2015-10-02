/*
  Analog input, analog output, serial output
 
 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.
 
 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground
 
 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
 
 */




// Analog input pin that the potentiometer is attached to
int th = 860;
int s0 = 0;
int s1 = 0;
int s2 = 0;


int v0 = 0;
int v1 = 0;
int v2 = 0;


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
}

void loop() {
  // read the analog in value:
  v0 = analogRead(A0);
//  v1 = analogRead(A1);
//  v2 = analogRead(A2);

  
  if (v0 > th) {
    s0 = 1;
  } else {
    s0 = 0;
  }
  
    if (v1 > th) {
    s1 = 1;
  } else {
    s1 = 0;
  }
  
    if (v2 > th) {
    s2 = 1;
  } else {
    s2 = 0;
  }
            

  // print the results to the serial monitor:
  Serial.print(s2); 
  Serial.print(s1); 
  Serial.print(s0);
  Serial.print("\t");
  Serial.print(v2);
  Serial.print("\t");
  Serial.print(v1);
  Serial.print("\t");
  Serial.print(v0);
  Serial.println("");

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(10);                     
}
