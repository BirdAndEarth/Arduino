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

int pot_pin = 11;
int det_pin = 3;
HardWire HWire(1, I2C_FAST_MODE); // I2c1
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);



String st = "";

void setup() {

  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC);
  pinMode(pot_pin, INPUT_ANALOG);
  pinMode(det_pin, INPUT_ANALOG);
  pinMode(33, OUTPUT);
  HWire.begin();




}


int adcStartValue = 1500;

void loop() {
  long now = millis();

  static int adc = adcStartValue;
  int potValue = 0;
  int adcValue = 0;
  int det_value = 0;
  float voltage_mv = 0;
  static boolean flg = false;
  static int count = 0;
  int d = 0;

//  potValue = analogRead(pot_pin);
//  det_value = analogRead(det_pin);
//  //  Serial.println(det_value);
//  adcValue = au(potValue);
//
//  digitalWrite(33, HIGH);
//  sendDac(adc);
//  voltage_mv = (float)((float)det_value / 4095 * 3.3);
//  updateDisplay(potValue, adc, voltage_mv);
//  delay(10);
  potValue = analogRead(pot_pin);
  sendDac(potValue);
  updateDisplay2(potValue);
  delay(10);
}


//==========================================================
int au(int inValue)
{
  int retValue = 0;
  retValue = (map(inValue, 5, 4090, 0, 4095));
  if (retValue > 4095) {
    retValue = 4095;
  }
  if (retValue < 0) {
    retValue = 0;
  }
  return retValue;
}

void on(int inValue)
{

}



//==========================================================
void updateDisplay(int potValue, int adcValue, float det)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  //  display.print("POT = ");
  //  display.println(potValue);
  display.print("");
  display.println(adcValue);
  //  display.print("");
  //  display.print(det, 3);
  //  display.println("V");
  display.display();

}

void updateDisplay2(int adcValue)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  //  display.print("POT = ");
  //  display.println(potValue);
  display.print("");
  display.println(adcValue);
  //  display.print("");
  //  display.print(det, 3);
  //  display.println("V");
  display.display();
}



//==========================================================
void sendDac(int value)
{
  if (value > 4095) value = 4095;
  if (value < 0) value = 0;
  HWire.beginTransmission(MCP4725_ADDR);
  HWire.write(64);                     // cmd to update the DAC
  HWire.write(value >> 4);        // the 8 most significant bits...
  HWire.write((value & 15) << 4); // the 4 least significant bits...
  HWire.endTransmission();
}

