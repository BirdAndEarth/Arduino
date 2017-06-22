#include <SPI.h>
#include <HardWire.h>
#include <Wire.h>
#include <WireBase.h>
#include <Adafruit_GFX_AS.h>
#include <Font16.h>
#include <Font32.h>
#include <Font64.h>
#include <Font7s.h>
#include <Load_fonts.h>
#include <Adafruit_SSD1306_STM32.h>

#define MCP4725_ADDR 0x60   

#define OLED_MOSI  4
#define OLED_CLK   6
#define OLED_CS    7
#define OLED_DC    8
#define OLED_RESET 9

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
//HardWire HWire(1, I2C_FAST_MODE); // I2c1

void setup() {


  pinMode(11, INPUT_ANALOG);
 //   HWire.begin();
display.begin(SSD1306_SWITCHCAPVCC);


  
}

void loop() {
  

}






void sendDac(int value)
{
  HWire.beginTransmission(MCP4725_ADDR);
  HWire.write(64);                     // cmd to update the DAC
  HWire.write(value >> 4);        // the 8 most significant bits...
  HWire.write((value & 15) << 4); // the 4 least significant bits...
  HWire.endTransmission();
}

