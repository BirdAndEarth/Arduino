#include "font5x7.h"
#include "slOled.h"

#define OLED_PIN_D7 22
#define OLED_PIN_D5 21
#define OLED_PIN_EN 20
#define OLED_PIN_RS 19

#define OLED_PIN_D6 8
#define OLED_PIN_D4 9
#define OLED_PIN_RW 10

#define OLED_PIN_PW 11

#define WIDTH    100
#define HEIGHT    16
#define GRAPHIC  200

void updateBmp() ;
void updateBmp() ;
void clearBmp() ;
void write4bits(uint8_t value) ;
void send(uint8_t value, uint8_t modeRS , uint8_t modeRW) ;
void command(uint8_t value) ;
void data_write(uint8_t value) ;
void pulseEnable() ;
void pinModeAll(uint8_t value) ;
void busy() ;
void sync() ;
void functionSet() ;
void displayOn() ;
void displayClear() ;
void entryModeSet() ;
void graphicModeSet() ;
void OLED_setup() ; //初期化
void OLED_Cursor(int col, int row) ;
void graphic_input(int col, byte * p) ;
void graphic_print(byte * p) ;


int bmp[HEIGHT][WIDTH] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

byte graphic[GRAPHIC];

void updateBmp() {
  byte b1 = 0x00;
  byte b2 = 0x00;

  for (int w = 0; w < WIDTH; w++) {
    b1 = 0x00;
    b2 = 0x00;

    for (int h = 0; h <= 7; h++) {
      if (bmp[h][w] == 1) {
        b1 |= 0x01 << h;
      }
    }

    graphic[(int)(w * 2 + 1) ] = b1;

    for (int h = 0; h <= 7; h++) {
      if (bmp[h + 8][w] == 1) {
        b2 |= 0x01 << h;
      }
    }
    graphic[(int)(w * 2) ] = b2;
  }
}

void clearBmp() {
  for (int w = 0; w <= WIDTH; w++) {
    for (int h = 0; h <= HEIGHT; h++) {
      bmp[h][w] = 0;
    }
  }
}

void write4bits(uint8_t value) {
  digitalWrite(OLED_PIN_D7, (value >> 3) & 0x01);
  digitalWrite(OLED_PIN_D6, (value >> 2) & 0x01);
  digitalWrite(OLED_PIN_D5, (value >> 1) & 0x01);
  digitalWrite(OLED_PIN_D4, value & 0x01);
  pulseEnable();
}

void send(uint8_t value, uint8_t modeRS , uint8_t modeRW) {
  digitalWrite(OLED_PIN_RS, modeRS);
  digitalWrite(OLED_PIN_RW, modeRW);
  write4bits(value >> 4);
  write4bits(value);
}

void command(uint8_t value) {
  busy();
  send(value, LOW, LOW);
}

void data_write(uint8_t value) {
  busy();
  send(value, HIGH, LOW);
}

void pulseEnable() {
  digitalWrite(OLED_PIN_EN, LOW);
  delayMicroseconds(1);
  digitalWrite(OLED_PIN_EN, HIGH);
  delayMicroseconds(1);
  digitalWrite(OLED_PIN_EN, LOW);
}

void pinModeAll(uint8_t value) {
  pinMode(OLED_PIN_RS, value);
  pinMode(OLED_PIN_RW, value);
  pinMode(OLED_PIN_EN, value);
  pinMode(OLED_PIN_D4, value);
  pinMode(OLED_PIN_D5, value);
  pinMode(OLED_PIN_D6, value);
  pinMode(OLED_PIN_D7, value);
}

void busy() {
  pinMode(OLED_PIN_D7, INPUT);
  int busy = HIGH;
  while (busy) {
    digitalWrite(OLED_PIN_RS, LOW);
    digitalWrite(OLED_PIN_RW, HIGH);
    pulseEnable();
    busy = digitalRead(OLED_PIN_D7);
    pulseEnable();
  }
  pinMode(OLED_PIN_D7, OUTPUT);
}

void sync() {
  busy();
  digitalWrite(OLED_PIN_RS, LOW);
  digitalWrite(OLED_PIN_RW, LOW);
  for (int i = 0; i < 5; i++) {
    write4bits(0x0);
  }
}

void functionSet() {
  busy();
  digitalWrite(OLED_PIN_RS, LOW);
  digitalWrite(OLED_PIN_RW, LOW);
  write4bits(0x2);
  command(0x28);//Function Set[0 0 1 DL N F FT1 FT0]//
}

void displayOn() {
  command(0x0c);//Display ON/OFF Control [0 0 0 0 1 D C B]
}

void displayClear() {
  command(0x01);
}

void returnHome() {
  command(0x02);
}

void entryModeSet() {
  command(0x06); // Entry Mode Set [0 0 0 0 0 0 0 1 I/D S]
}

void graphicModeSet() {
  command(0x1f); // Cursor / Display Shift / Mode / Pwr[ 0 0 0 1 G/C PWR 1 1]

  //{I/D:INCREMENT/DECREMENT BIT [1:右 0:左]}カソールを動かす方向
  //{S:SHIFT ENTIRE DISPLAY CONTROL BIT [1:する 0:しない]}全体シフト
  //{D:DISPLAY ON/OFF BIT [1:ON 0:OFF]}ディスプレイの点灯
  //{C:CURSOR DISPLAY CONTROL BIT [1:ON 0:OFF]}カソールのありなし
  //{B:BLINKING CONTROL BIT [1:する 0:しない]}点滅するかどうか？
  //{S/C:[1:表示とカソール 0:カソール]}シフトするもの
  //{R/L:[1:右 0:左]}右左
  //{G/C:GRAPHIC MODE / CHARACTER MODE SELECTION [1:グラフィック 0:キャラクタ]}モード選択
  //{PWR:ENABLE/DISABLE INTERNAL POWER [1:ON 0:OFF]}DCDCコンバータのON・OFF
  //{DL:INTERFACE DATA LENGTH CONTROL BIT [1:8bit 0:4bit]}インタフェイス選択
  //{N:NUMBER OF DISPLAY LINE [1:2行 0:1行]}行数 //グラフィックモードの時は２行にしないと11×100ドットになるらしい。
  //{F:CHARACTER FONT SET [1:5×10 0:5×8]}フォントセット
  //{FT1:FONT TABLE SELECTION [1: 0:]} テーブルデフォ0
  //{FT0:FONT TABLE SELECTION [1: 0:]} テーブルデフォ0
}









void OLED_setup() { //初期化

  pinMode(OLED_PIN_PW, OUTPUT);
  digitalWrite(OLED_PIN_PW, LOW);
  delay(500);
  digitalWrite(OLED_PIN_PW, HIGH);
  delay(500);
  pinModeAll(OUTPUT);
  sync();
  functionSet();
  displayOn();
  entryModeSet();
  graphicModeSet();
  displayClear();
  returnHome();
}
void OLED_Cursor(int col, int row) {
  command((0x80 | col));
  command((0x40 | row));
}

void graphic_input(int col, byte * p) {
  for (int i = 1; i < 20; i = i + 2) {
    graphic[i + col] |= p[i];
  }
  for (int i = 0; i < 20; i = i + 2) {
    graphic[i + col] |= p[i];
  }
}


void graphic_print(byte * p) {
  returnHome();
  for (int i = 1; i < 200; i = i + 2) {
    data_write(p[i]);
  }
  for (int i = 0; i < 200; i = i + 2) {
    data_write(p[i]);
  }
}
