#include <AlphaRemote.h>


// for DaVinci32U Pin out
#include"dv32u.h"

// Serial
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int ledPin = 13;
int irLedPin = PF4;

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  AlphaRemote.begin(PF4);
  inputString.reserve(200);
}

void loop()
{
  serialEvent();
  if (stringComplete) {

    digitalWrite(ledPin, HIGH);

    switch (inputString.toInt()){
    case 0:
      AlphaRemote.Shutter();
      break;
    case 1:
      AlphaRemote.Shutter2s();
      break;
    case 2:
      AlphaRemote.Rec();
      break;
    }
    digitalWrite(ledPin, LOW);

    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
    else {
      inputString += inChar;
    }
  }
}






















