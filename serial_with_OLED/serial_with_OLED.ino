#include <WiiChuck.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "dv32u.h"
//#include "nunchuck_funcs.h"

#define S5851_ADDR 0x48
#define OLED_RESET PD2

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

int LED = PC7;
int intTemp = 0;
int StoredData = 0;
float temp = 0;
WiiChuck chuck = WiiChuck();
int x = 0;
int y = 0;

void setup()   {                
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  pinMode(LED,OUTPUT);
  chuck.begin();
  chuck.update();
  digitalWrite(LED,LOW);  
  Wire.begin();  
  delay(1);

}


void loop() {

  // miniature bitmap display
  static unsigned char i = 0;
  if(i == 100){
    i = 0; 
  }

//    tempRead();
  delay(1);

  chuck.update(); 
  delay(1);

  display.clearDisplay();

//  display.drawBitmap(1, 2,  logo16_glcd_bmp, LOGO16_GLCD_WIDTH, LOGO16_GLCD_HEIGHT, 1);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(1,1);
//  display.println(i); 
//    display.print(" ");  

  //display.print(" ");
//  display.write(247);  
//  display.println("C");
  
//  display.println(chuck.readJoyX());
//  display.print(" ");  
//  display.println(chuck.readJoyY());


  x =  (int)((chuck.readJoyX() - 2) / 2 +0);
  y = -(int)((chuck.readJoyY()+1) / 8 +0);
  
//  x =  (int)(chuck.readJoyX());
//  y = -(int)(chuck.readJoyY());
  
  display.print(chuck.readJoyX()-2);
  display.println(" ");  
  display.println(chuck.readJoyY()+1);


  display.drawLine(70, 15, x+70, y+15, WHITE);


//  display.drawPixel(x+70, y+15, WHITE);






/*
  display.print(" ");
  display.print(chuck.cPressed());
  display.print(" ");
  display.print(chuck.zPressed());
  display.println(" ");
  display.display();
  */
    display.display();

  i++;
}





// -------------------------------------------------------
void chucky() {
  delay(1);
  chuck.update(); 


  Serial.print(chuck.readJoyX());
    Serial.print("\t");  
  Serial.print(chuck.readJoyY());
    Serial.print("\t");
  Serial.print(chuck.cPressed());
    Serial.print("\t");
  Serial.print(chuck.zPressed());
    Serial.print("\t");
  
  
  
    
/*
    Serial.print((int)chuck.readAccelX()); 
    Serial.print(", ");  
    Serial.print((int)chuck.readAccelY()); 
    Serial.print(", ");  

    Serial.print((int)chuck.readAccelZ()); 
*/
    Serial.println();

}




// S-5851  ////////////////////////////////////////////////////
void tempRead()
{
  int data1=0;
  int data2=0;
  int data=0;
  temp = 0;

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

    StoredData = data;
    intTemp = data;    
  } 
  else {
    intTemp=999; 
  }
  Wire.endTransmission();
}

