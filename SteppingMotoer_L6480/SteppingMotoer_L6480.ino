
/*******************************

  コイル巻き機用  Rev. 0.0
  2014/09/26 Shuichi Yokota
  
  Nunchuckでの動作確認はOK。
  諸パラメータも問題なさそう。
  
********************************/

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
#define PIN_STBY     15


#define DBG 0

WiiChuck chuck = WiiChuck();
long x = 0;
int y = 0;
int c = 0;
int z = 0;


unsigned long MAX_SPEED = 0x35;//[R, WR]最大速度default 0x041 (10bit) (15.25*val+15.25[step/s])

unsigned long spd = 0;
unsigned int dia = 0;



void setup()
{
  pinMode(PIN_SPI_MOSI, OUTPUT);
  pinMode(PIN_SPI_MISO, INPUT);
  pinMode(PIN_SPI_SCK, OUTPUT);
  pinMode(PIN_SPI_SS, OUTPUT);
  pinMode(PIN_BUSY, INPUT);
    pinMode(PIN_STBY, OUTPUT);

  digitalWrite(PIN_STBY, HIGH);

  pinMode(13, OUTPUT);

  Wire.begin();
  SPI.begin();
  chuck.begin();

  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  Serial.begin(115200);
  digitalWrite(PIN_SPI_SS, HIGH);
  delay(100);

  Serial.println("Reset & Setup");


  L6480_resetdevice(); //残留コマンドの削除とリセット
  L6480_setup();  //L6480を設定

  //MsTimer2::set(10, chucky);
  //MsTimer2::start();
  delay(100);
  Serial.println("Resetpos");

  L6480_resetpos();
  delay(100);
  //L6480_run(1, 0xFFFF);




}

void loop(){

  chucky();
  delay(100);
}

void L6480_setup(){
//  L6470_setparam_acc(0x3ff); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
//  L6470_setparam_dec(0x3ff); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
//  L6470_setparam_maxspeed(MAX_SPEED); //default 0x041 (10bit) (15.25*val+15.25[step/s])
//  L6470_setparam_minspeed(0x00); //default 0x000 (1+12bit) (0.238*val[step/s])
//  L6470_setparam_fsspd(0x027); //default 0x027 (10bit) (15.25*val+7.63[step/s])
//  L6470_setparam_kvalhold(0x29); //default 0x29 (8bit) (Vs[V]*val/256)
//  L6470_setparam_kvalrun(0x90); //default 0x29 (8bit) (Vs[V]*val/256)
//  L6470_setparam_kvalacc(0x90); //default 0x29 (8bit) (Vs[V]*val/256)
//  L6470_setparam_kvaldec(0x90); //default 0x29 (8bit) (Vs[V]*val/256)
//
//  L6470_setparam_stepmood(0x03); //default 0x07 (1+3+1+3bit)

  L6480_setparam_acc(0x3ff); //[R, WS] 加速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  L6480_setparam_dec(0x3ff); //[R, WS] 減速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  L6480_setparam_maxspeed(MAX_SPEED); //[R, WR]最大速度default 0x041 (10bit) (15.25*val+15.25[step/s])
  L6480_setparam_minspeed(0x0000); //[R, WS]最小速度default 0x0000 (1+12bit) (0.238*val+[step/s])
  L6480_setparam_fsspd(0x027); //[R, WR]μステップからフルステップへの切替点速度default 0x027 (10bit) (15.25*val+7.63[step/s])

  L6480_setparam_kvalhold(0x29); //[R, WR]停止時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  L6480_setparam_kvalrun(0x29); //[R, WR]定速回転時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  L6480_setparam_kvalacc(0x29); //[R, WR]加速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  L6480_setparam_kvaldec(0x29); //[R, WR]減速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)

  L6480_setparam_intspd(0x508); //245[R, WH]逆起電力補償切替点速度default 0x0408 (14bit) (0.238*val[step/s])
  L6480_setparam_stslp(0x26); //[R, WH]逆起電力補償低速時勾配default 0x19 (8bit) (0.000015*val[% s/step])
  L6480_setparam_fnslpacc(0x65); //[R, WH]逆起電力補償高速時加速勾配default 0x29 (8bit) (0.000015*val[% s/step])
  L6480_setparam_fnslpdec(0x65); //[R, WH]逆起電力補償高速時減速勾配default 0x29 (8bit) (0.000015*val[% s/step])
  L6480_setparam_ktherm(0x1); //[R, WR]不明default 0x0 (4bit) (0.03125*val+1)
  L6480_setparam_ocdth(0x1f); //[R, WR]過電流しきい値default 0x8 (5bit) (31.25*val+31.25[mV])
  L6480_setparam_stallth(0x1f); //[R, WR]失速電流しきい値？default 0x10 (5bit) (31.25*val+31.25[mV])
  L6480_setparam_stepmood(0x03); //[R, WH]ステップモードdefault 0x07 (8bit)L6480_setparam_alareen(val); //[R, WS]有効アラームdefault 0xff (1+1+1+1+1+1+1+1bit)
  L6480_setparam_alareen(0xde); //[R, WS]有効アラームdefault 0xff (1+1+1+1+1+1+1+1bit)
  L6480_setparam_gatecfg1(0x000);//[R, WH]geta driver configuration //default 0x000(1+3+3+5bit)
  L6480_setparam_gatecfg2(0x00);//[R, WH]geta driver configuration //default 0x00(3+5bit)
  L6480_setparam_config(0x3728); //[R, WH]各種設定default 0x2e88 (3+3+1+1+1+1+1+1+1+3bit)  


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


    if(spd > 53000){
      spd = 53000;
    }
    if(y < 0){
      dia = 1;
    }
    else {
      dia = 0;
    }

    L6480_run(dia, spd);



    //    Serial.print("dia = ");
    //Serial.print(dia);
//    Serial.print(" spd = ");
    //   Serial.println(spd);
    Serial.println((float)L6480_getparam_abspos()/(float)1600);
  }

  else {
    L6480_softstop();
    //Serial.println("Stop");

  }


  if(c == 1){
    
    
    Serial.println("GO HOME");

    L6480_setparam_acc(0xff); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
    L6480_setparam_dec(0xf); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
    L6480_gohome();
    L6480_setparam_acc(0x0ff); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
    L6480_setparam_dec(0x0ff); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])

    Serial.println((float)L6480_getparam_abspos()/(float)1600);


  }
  if(z == 1){
    L6480_resetpos();
    Serial.println("RESET");
    delay(1000);
    Serial.println((float)L6480_getparam_abspos()/(float)1600);
  }




//  Serial.print( L6480_getparam_abspos(),DEC);
//  Serial.print("  ");
//  Serial.println( L6480_getparam_speed(),DEC);

}











