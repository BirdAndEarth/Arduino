#include <SPI.h>
#include <MsTimer2.h>
#include "dv32u.h"
#include <WiiChuck.h>
#include <Wire.h>
#include <math.h>


// ピン定義。
#define PIN_SPI_SS   10
#define PIN_SPI_SCK  11
#define PIN_SPI_MOSI 12
#define PIN_SPI_MISO 13
#define PIN_BUSY     14

#define DBG 0

WiiChuck chuck = WiiChuck();
long x = 0;
int y = 0;
int c = 0;
int z = 0;


unsigned long MAX_SPEED = 0x30;

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
  delay(1000);

  Serial.println("Reset & Setup");


  L6470_resetdevice(); //残留コマンドの削除とリセット
  L6470_setup();  //L6470を設定

  //MsTimer2::set(10, chucky);
  //MsTimer2::start();
  delay(1000);
  Serial.println("Resetpos");

//  L6470_resetpos();
  delay(1000);
  //L6470_run(1, 0xFFFF);




}

void loop(){

  chucky();
  delay(100);
}

void L6470_setup(){
  L6470_setparam_acc(0x3ff); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  L6470_setparam_dec(0x3ff); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  L6470_setparam_maxspeed(MAX_SPEED); //default 0x041 (10bit) (15.25*val+15.25[step/s])
  L6470_setparam_minspeed(0x00); //default 0x000 (1+12bit) (0.238*val[step/s])
  L6470_setparam_fsspd(0x027); //default 0x027 (10bit) (15.25*val+7.63[step/s])
  L6470_setparam_kvalhold(0x29); //default 0x29 (8bit) (Vs[V]*val/256)
  L6470_setparam_kvalrun(0xA0); //default 0x29 (8bit) (Vs[V]*val/256)
  L6470_setparam_kvalacc(0xA0); //default 0x29 (8bit) (Vs[V]*val/256)
  L6470_setparam_kvaldec(0xA0); //default 0x29 (8bit) (Vs[V]*val/256)

  L6470_setparam_stepmood(0x03); //default 0x07 (1+3+1+3bit)
}

void chucky(){



  chuck.update();
  x = chuck.readJoyX();
  y = chuck.readJoyY();
  c = chuck.cPressed();
  z = chuck.zPressed();

  // Serial.print(y);


  if (abs(y) > 3){

    spd = (long)10*(long)y*(long)y;


    if(spd > 45000){
      spd = 45000;
    }
    if(y < 0){
      dia = 1;
    }
    else {
      dia = 0;
    }

    L6470_run(dia, spd);



    //    Serial.print("dia = ");
    //Serial.print(dia);
//    Serial.print(" spd = ");
    //   Serial.println(spd);
//    Serial.print((float)L6470_getparam_abspos());
//    Serial.print(" ");

    Serial.println((float)L6470_getparam_abspos()/(float)1600);
    
  }

  else {
    L6470_softstop();
    //Serial.println("Stop");

  }


  if(c == 1){
    
    
    Serial.println("GO HOME");

    L6470_setparam_acc(0xff); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
    L6470_setparam_dec(0xf); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
    L6470_gohome();
    L6470_setparam_acc(0x0ff); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
    L6470_setparam_dec(0x0ff); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])

    Serial.println((float)L6470_getparam_abspos()/(float)1600);


  }
  if(z == 1){
    L6470_resetpos();
    Serial.println("RESET");
    delay(1000);
    Serial.println((float)L6470_getparam_abspos()/(float)1600);
        //Serial.println(L6470_getparam_abspos());

    
  }




  //  Serial.print( L6470_getparam_abspos(),DEC);
  //  Serial.print("  ");
  //  Serial.println( L6470_getparam_speed(),DEC);

}











