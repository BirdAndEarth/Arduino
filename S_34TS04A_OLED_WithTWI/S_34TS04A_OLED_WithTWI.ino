
/*********************************************
 * I2C接続のOLEDモジュールでS-34TS04Aの温度を表示したりするスケッチ。
 * S-34TS04A READ and WRITE W/ S-5851, SSD1306
 * shiu 2013/07/08
 * 
 * PIN CONFIGURE
 *
 *-I2C
 * SCL PD0
 * SDA PD1
 * 
 *-OLED RESET PD2
 *
 *-S34TS04A
 * SCL   PD4
 * SDA   PD5
 * SA1   PD6
 * Relay PC6
 * 
 *********************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#include "dv32u.h"
#include "s34ts04a.h"

#define S5851_ADDR 0x48
#define OLED_RESET PD7

#define R 1
#define W 0

#define ACK 1
#define NACK 0



int relayPin = PC6;
int in = 0;

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


int flg = 0;
int flg2 = 0;
int intTsReadFast = 0;
int intTsRead = 0;
unsigned long TimeStart = 0;
unsigned long TimeNow = 0;




void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  Wire.begin();  
  pinMode(relayPin, OUTPUT);
  pinMode(PB0, INPUT_PULLUP);
  pinMode(PC6, OUTPUT);

  //  pinMode(PD2, OUTPUT);
  delay(5);
  I2C_init();
  delay(5);
  digitalWrite(relayPin, LOW);
  digitalWrite(PC7, LOW);

  //  digitalWrite(PD2, LOW);
}



void loop()
{


  while (flg == 0) {
    TimeStart = millis();
    intTsRead = TsRead();
    digitalWrite(PC7, HIGH);

    if (intTsRead != 4095){
      flg = 1;
      TimeNow = millis();
      Serial.print(TimeNow - TimeStart);
      Serial.print("\t");
      Serial.println(intTsRead * 0.0625);
      Serial1.print(TimeNow - TimeStart);
      Serial1.print("\t");
      Serial1.println(intTsRead * 0.0625);

    } 
    else {
      flg = 0;
      flg2 = 0;
      dispNoSignal();
    }
    digitalWrite(PC7, LOW);

  }

  digitalWrite(PC7, HIGH);


  if (flg2 != 0) {
    intTsRead = TsReadFast();
  }
  else {
    intTsRead = TsRead();
    flg2 = 1;
  }


  TimeNow = millis();
  digitalWrite(PC7, LOW);

  if (intTsRead != 4095) {

    Serial.print(TimeNow - TimeStart);
    Serial.print("\t");
    Serial.println(intTsRead * 0.0625);

//    Serial1.print(TimeNow - TimeStart);
//    Serial1.print("\t");
//    Serial1.println(intTsRead * 0.0625);


    disp(intTsRead * 0.0625);
  } 
  else {
    flg = 0;
    flg2 = 0;
    dispNoSignal();
        Serial.println("");
        Serial1.println("");


  }

  digitalWrite(PC7, LOW);





  /*
  if (in == 0){
   TsRead();
   }
   
   // Write
   if (digitalRead(PB0) == LOW && tempRead() != 0)
   {
   }
   
   digitalWrite(PC7, HIGH);
   
   display.clearDisplay();
   display.setTextColor(WHITE);
   display.setTextSize(1);
   
   display.setCursor(0,1);
   display.print("S-34TS04A");
   
   display.setCursor(0,13);
   display.setTextSize(2);
   display.print(TsReadFast()*0.0625);
  /*
   if (tempRead() != 0){
   display.setTextSize(1);
   display.setCursor(68,1);
   display.print("S-5851");
   
   display.setTextSize(2);
   display.setCursor(68,13);
   display.print(tempRead());
   
   display.setCursor(0,13);
   display.setTextSize(2);
   display.print(TsReadFast()*0.0625);
   
   }
   else {
   display.setCursor(0,13);
   display.setTextSize(2);
   display.print(TsRead()*0.0625);
   }
   
   display.display();
   
   */
  //  digitalWrite(PC7, LOW);


  //  delay(47);


  //  in++;

}


// --OLED ----------------------------

void disp(float temp)
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(3);
  display.print(temp);
  display.write(247);
  display.print("C");
  display.setTextSize(1);
  display.setCursor(0,24);
  display.print("S-34TS04A ");
  display.print(TimeNow - TimeStart);
  display.print("ms");
  display.display();
}

void dispNoSignal()
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(1);

//  for(int i = 50; i < 255; i++){
//    display.write(i);
//  }

display.print("NO SIGNAL.");


  display.display();
}



// --Read and Write S-34TS04A ----------------------------
void TsWriteTemp(float temperature)
{
  int nt = 0;
  int t = 0;
  int ofs = 0;
  float ta = tempRead();
  uint8_t ofsbit = 0;


  TsWrite(0x00);
  nt = TsRead();
  ofsbit = nt - (int)(ta / 0.0625 + 0.5);

  TsWrite(ofsbit);

  Serial.print("nt = ");
  Serial.println(nt);

  Serial.print("ta = ");
  Serial.println((int)(ta / 0.0625 + 0.5));

  Serial.print("ofsbit = ");
  Serial.println(ofsbit);

  delay(1000);
  TsRead();
}



void TsWrite(uint8_t ofsbit)
{
  PowerOn();
  delay(10);

  // TS ShutDownMode Set
  I2C_start();
  I2C_write(B00110000);
  I2C_write(0x01);
  I2C_write(0x01);
  I2C_write(0x00);
  I2C_stop();

  // Test Enable set
  I2C_start_testmode();
  I2C_write_testmode(B01010101);
  I2C_start_testmode();
  I2C_write_testmode(B11101010);
  I2C_start_testmode();
  I2C_write(B01001010);
  I2C_write(B00001111);
  I2C_write(ofsbit);
  I2C_stop();


  delay(10);

  PowerOff();

  delay(300);
}

int TsRead()
{
  uint8_t data1 = 0;
  uint8_t data2 = 0;
  unsigned int data = 0;


  PowerOn();

  //  delay(10);

  // TS Shut Down Mode Set
  I2C_start();
  I2C_write(B00110000);
  I2C_write(B00000001);
  I2C_write(B00000001);
  I2C_write(B00000000);
  I2C_stop();

  // Resolution
  I2C_start();
  I2C_write(B00110000);
  I2C_write(B00001000);
  I2C_write(B00000000);
  I2C_write(B00000011);
  I2C_stop();

  // TS ShutDownModeRelease
  I2C_start();
  I2C_write(B00110000);
  I2C_write(B00000001);
  I2C_write(B00000000);
  I2C_write(B00000000);
  I2C_stop();

  delay(100);

  // Ambient Temperature Read
  I2C_start();
  I2C_write(B00110000); // Address + 0
  I2C_write(B00000101); // Register 0x85
  I2C_start();
  I2C_write(B00110001); // Address + 1
  data1 = I2C_read(ACK);
  data2 = I2C_read(NACK);
  I2C_stop();

  data1 = data1 & B1111;
  data = (data1 << 8) + data2;

  return data;

}


int TsReadFast(){
  uint8_t data1 = 0;
  uint8_t data2 = 0;
  unsigned int data = 0;

  // Ambient Temperature Read
  I2C_start();
  I2C_write(B00110000); // Address + 0
  I2C_write(B00000101); // Register 0x85
  I2C_start();
  I2C_write(B00110001); // Address + 1
  data1 = I2C_read(ACK);
  data2 = I2C_read(NACK);
  I2C_stop();

  data1 = data1 & B1111;
  data = (data1 << 8) + data2;

  return data;
}



void PowerOn()
{
  digitalWrite(relayPin, HIGH);
}
void PowerOff()
{
  digitalWrite(relayPin, LOW);
}


float tempRead()
{
  int data1=0;
  int data2=0;
  int data=0;
  float temp = 0;

  //Dummy Write
  Wire.beginTransmission(S5851_ADDR);
  Wire.write(0x00);

  //Read Data 
  Wire.requestFrom(S5851_ADDR, 2);
  if (Wire.available()) {
    data1 = Wire.read();
    data2 = Wire.read();

    data1= data1 << 8;
    data = data1 + data2;
    data = data >> 4;
    //temp = (data + (8 / 1596 *data - 4)) * 0.0625;
    temp = (data + (8 / 1592 * data - (4 + 32 / 1592))) * 0.0625;


    //data = temp * 10;
  } 
  else {
    return temp;
  }
  Wire.endTransmission();

  return temp;
}

















