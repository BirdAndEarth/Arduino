#include <NeoMaple.h>


#define NUMPIXELS      3

NeoMaple pixels = NeoMaple(NUMPIXELS, NEO_GRB + NEO_KHZ800);

int powerPin = 3;
int mcuButtonPin = 32;
int mcuLedPin = 33;

int de = 500;


/****************************************************/
void powerOn() {
  digitalWrite(powerPin , HIGH);
  digitalWrite(mcuLedPin, HIGH);
}

void powerOff() {
  digitalWrite(powerPin , LOW);
  digitalWrite(mcuLedPin , LOW);
}





/****************************************************/
void setup() {
  pinMode(powerPin, OUTPUT);
  pinMode(mcuButtonPin, INPUT);
  pinMode(mcuLedPin, OUTPUT);

  digitalWrite(powerPin, LOW);
  digitalWrite(mcuButtonPin, LOW);
  digitalWrite(mcuLedPin , LOW);

  pixels.begin();

  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Moderately bright green color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(10);

  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Moderately bright green color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(10);


}

void loop() {

  if (!digitalRead(mcuButtonPin)) {
    powerOn();
  } else {
    powerOff();
  }

  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Moderately bright green color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(de); // Delay for a period of time (in milliseconds).

  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // Moderately bright green color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(de); // Delay for a period of time (in milliseconds).

  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 0, 255)); // Moderately bright green color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(de); // Delay for a period of time (in milliseconds).
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255, 255, 255)); // Moderately bright green color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(de); // Delay for a period of time (in milliseconds).

}



