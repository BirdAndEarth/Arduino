#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 11


Adafruit_SSD1306 display(OLED_RESET);

#define LOGO16_GLCD_HEIGHT 8 
#define LOGO16_GLCD_WIDTH  43 
static unsigned char PROGMEM logo16_glcd_bmp[] =
{ 
  B11111111, B00000000, B00000000, B00000000, B00000000, B00000000,
  B10000001, B00111110, B00000011, B11100000, B10000000, B00000000,
  B10100101, B00001011, B10111010, B10101110, B10101110, B11100000,
  B10100101, B00001010, B10101010, B10100010, B10101010, B10000000,
  B10000001, B00001010, B10111010, B10101110, B11001110, B10000000,
  B10011001, B00001010, B10100010, B10101010, B10101000, B10000000,
  B10000001, B00001010, B10111010, B10101110, B10101110, B10000000,
  B11111101, B00000000, B00000000, B00000000, B00000000, B00000000
};

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup()
{
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  Wire.begin();  
  inputString.reserve(200);
  
  
  inputString = "";
      dispEl();

}

void loop()
{
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString); 
    // clear the string:
    dispEl();
    inputString = "";
    stringComplete = false;
  }
}

void dispEl(){
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(50,0);
    display.setTextSize(2);
    display.println(inputString);
    display.display();
}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}




