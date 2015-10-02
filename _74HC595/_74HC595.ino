// ----------------------------------
// 74HC595 DaVinci32U
//                  2013/03/13 Yo
// ----------------------------------

#include <avr/io.h>

// For Davinci 32U PinOut
#define PB0 17
#define PB1 15
#define PB2 16
#define PB3 14
#define PB4  8
#define PB5  9
#define PB6 10
#define PB7 11
#define PC6  5
#define PC7 13
#define PD0  3
#define PD1  2
#define PD2  0
#define PD3  1
#define PD4  4
#define PD6 12
#define PD7  6
#define PE6 7
#define PF0  23
#define PF1  22
#define PF4  21
#define PF5  20
#define PF6  19
#define PF7  18

#define NUM_UNIT 2

#define DBG 0


int pinSCL  = PB0;
int pinSCK  = PB1;
int pinRCK  = PB2;
int pinSER  = PB4;
int pinGATE = PB3;

uint8_t B[NUM_UNIT];
int MAX_BIT = 8 * NUM_UNIT -1;
int wait = 50;

void setup()
{
  pinMode(pinSCL,OUTPUT);
  pinMode(pinSCK,OUTPUT);
  pinMode(pinRCK,OUTPUT);
  pinMode(pinSER,OUTPUT);
  pinMode(pinGATE,OUTPUT);

  digitalWrite(pinSCL,HIGH);  
  digitalWrite(pinSCK,LOW);
  digitalWrite(pinRCK,LOW);
  digitalWrite(pinSER,LOW);
  digitalWrite(pinGATE,LOW);

//  Serial.begin(115200);


  srClear();
  delay(2000);
}

void loop()
{
  int i;
  uint16_t data;

  for (int i = 0; i <= 0xFFFF; i++){
    B[1] = (i >> 8) & 0xFF;
    B[0] = i & 0xFF;
    srSet(B);
//    delay(100);
  }
} 

// ----------------------------------------




/**********************************
 * Shift resistor control functions
 **********************************/

//Clear shift resistor(s)
void srClear()
{
  digitalWrite(pinSCL,LOW);
  _sckOut();
  digitalWrite(pinSCL,HIGH);
}

//Send serial data to shift resistor(s)
void srSet(uint8_t data[])
{
  for (int j = NUM_UNIT - 1; j >=0; j--){
    for (int i = 7; i >= 0; i--){
      _serOut((data[j] >> i) & 1);
      _sckOut();
    }
  }

  _rckOut();
}

//Reflesh shift resistor(s) (RCK)
void srRefresh()
{
  _rckOut();
}

//------------------------------------------
void _sckOut() // Out a clock to pinSCK
{
  digitalWrite(pinSCK,HIGH);
  digitalWrite(pinSCK,LOW);
}
void _rckOut() // Out a clock to pinRCK
{
  digitalWrite(pinRCK,HIGH);
  digitalWrite(pinRCK,LOW);
}
void _serOut(uint8_t bit) // Out a datum to pinSER
{
  if(bit) {
    digitalWrite(pinSER,HIGH);
  } 
  else {
    digitalWrite(pinSER,LOW);    
  }
}
//------------------------------------------



















