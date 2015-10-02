#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_DC 11
#define OLED_CS 12
#define OLED_CLK 10
#define OLED_MOSI 9
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


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
String dbgString = "$$$";
boolean stringComplete = false;  // whether the string is complete

int textSize = 1;
int i = 0;

void setup()
{
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  Wire.begin();  
  inputString.reserve(200);
}

void loop()
{
  if (stringComplete) {
    //Serial.print(inputString);
    if (inputString == dbgString) {
      //dispEl("Enter Debug Mode!");
      stringComplete = false;
      inputString = "";
      dbgMode();
      inputString = "";
      //dispEl(inputString);
    } else {
    dispEl(inputString);
    inputString = "";
    stringComplete = false;
    }
  }
}

void dispEl(String str){
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(textSize);
  display.println(str);
  display.display();
}



void dbgMode(){

  int mode = 0;
  int DbgMode = 1;

  while(DbgMode == 1) {
    if (stringComplete) {
      switch (inputString.toInt()) {
        Serial.print("input Char = ");
        Serial.println(inputString.toInt());
      case 1:
        textSize = 1;
        break;
      case 2:
        textSize = 2;
        break;
      case 3:
        textSize = 3;
        break;
      case 4:
        textSize = 4;
        break;
      case 5:
        textSize = 5;
        break;
      default:
        textSize = 1;
        dispEl("oh My god Default");
      }
      DbgMode = 0;
      stringComplete = false;
    }
    if (serialEventRun) serialEventRun();
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    } 
    else {
      inputString += inChar;
    }

  }
}



















