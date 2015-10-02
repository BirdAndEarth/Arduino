#include <SPI.h>
#include <MsTimer2.h>
#include "dv32u.h"
#include <WiiChuck.h>
#include <Wire.h>
#include <math.h>


// ピン定義。
#define PIN_SPI_SS   PB0
#define PIN_SPI_SCK  PB1
#define PIN_SPI_MOSI PB2
#define PIN_SPI_MISO PB3
#define PIN_BUSY     PB4


WiiChuck chuck = WiiChuck();
 long x = 0;
 int y = 0;
 int c = 0;
 int z = 0;
 

 unsigned long MAX_SPEED = 0x29;

 unsigned long spd = 0;
 unsigned int dia = 0;



void setup()
{
  pinMode(PIN_SPI_MOSI, OUTPUT);
  pinMode(PIN_SPI_MISO, INPUT);
  pinMode(PIN_SPI_SCK, OUTPUT);
  pinMode(PIN_SPI_SS, OUTPUT);
  pinMode(PIN_BUSY, INPUT);
  pinMode(13, OUTPUT);

  Wire.begin();
  SPI.begin();
    chuck.begin();

  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  Serial.begin(115200);
  digitalWrite(PIN_SPI_SS, HIGH);

  L6470_resetdevice(); //残留コマンドの削除とリセット
  L6470_setup();  //L6470を設定

//  MsTimer2::set(10, chucky);
//  MsTimer2::start();
  delay(1000);
  L6470_resetpos();
  delay(100);
      //L6470_run(1, 0xFFFF);

  
  
  
}

void loop(){
chucky();
delay(5);
}

void L6470_setup(){
  L6470_setparam_acc(0x3ff); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  L6470_setparam_dec(0x3ff); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  L6470_setparam_maxspeed(MAX_SPEED); //default 0x041 (10bit) (15.25*val+15.25[step/s])
  L6470_setparam_minspeed(0x00); //default 0x000 (1+12bit) (0.238*val[step/s])
  L6470_setparam_fsspd(0x3ff); //default 0x027 (10bit) (15.25*val+7.63[step/s])
  L6470_setparam_kvalhold(0x20); //default 0x29 (8bit) (Vs[V]*val/256)
  L6470_setparam_kvalrun(0x60); //default 0x29 (8bit) (Vs[V]*val/256)
  L6470_setparam_kvalacc(0x60); //default 0x29 (8bit) (Vs[V]*val/256)
  L6470_setparam_kvaldec(0x60); //default 0x29 (8bit) (Vs[V]*val/256)

  L6470_setparam_stepmood(0x07); //default 0x07 (1+3+1+3bit)
}

void chucky(){



  chuck.update();
  x = chuck.readJoyX();
  y = chuck.readJoyY();
  c = chuck.cPressed();
  z = chuck.zPressed();

//Serial.println(x);
  if (abs(x) > 3){

      spd = 7*(abs(x)-3)*(abs(x)-3);

    if(x < 0){
      dia = 1;
    }
    else {
      dia = 0;
    }

    L6470_run(dia, spd);

//    Serial.print("dia = ");
//    Serial.println(dia);
//    Serial.print("spd = ");
//    Serial.println(spd);
  }

  else {
    L6470_softstop();
//    Serial.println("Stop");

  }
  
  
  if(c == 1){
  L6470_setparam_acc(0xff); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  L6470_setparam_dec(0xf); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
    L6470_gohome();
  L6470_setparam_acc(0x3ff); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  L6470_setparam_dec(0x3ff); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])



}
  if(z == 1){L6470_resetpos();}
  
  
  
  
  Serial.print( L6470_getparam_abspos(),DEC);
  Serial.print("  ");
  Serial.println( L6470_getparam_speed(),DEC);

}









