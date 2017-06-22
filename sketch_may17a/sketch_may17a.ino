#include <SoftwareSerial.h>

int led = 0;
int d = 100;

SoftwareSerial mySerial(1, 2); // RX, TX
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  mySerial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  char c;
  if (mySerial.available()) {
    while (mySerial.available()) {
      digitalWrite(led, HIGH);
      c = mySerial.read();
      mySerial.print(c);
      digitalWrite(led, LOW);
    }

  }
}
