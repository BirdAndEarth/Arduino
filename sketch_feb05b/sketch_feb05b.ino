#define OLED_PIN_PW 5
#define OLED_PIN_RS 6
#define OLED_PIN_RW 7
#define OLED_PIN_EN 8
#define OLED_PIN_D7 12
#define OLED_PIN_D6 11
#define OLED_PIN_D5 10
#define OLED_PIN_D4 9
 
byte grafic[200] = {
  B01000000,B00000000
    ,B01111000,B00000000
    ,B00111111,B00000000
    ,B00001111,B11100000
    ,B00001100,B11111000
    ,B00001100,B00111111
    ,B00001100,B00000111
    ,B00001100,B00111111
    ,B00001100,B11111000
    ,B00001111,B11100000
    ,B00111111,B00000000
    ,B01111000,B00000000
    ,B01000000,B00000000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B01111111,B11110000
    ,B01111111,B11110000
    ,B00000000,B01100000
    ,B00000000,B00110000
    ,B00000000,B00110000
    ,B00000000,B00110000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00001111,B10000000
    ,B00111111,B11100000
    ,B01110000,B01110000
    ,B01100000,B00110000
    ,B01100000,B00110000
    ,B01100000,B00110000
    ,B01100000,B00110000
    ,B00110000,B01100000
    ,B01111111,B11111111
    ,B01111111,B11111111
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00011111,B11110000
    ,B00111111,B11110000
    ,B01110000,B00000000
    ,B01100000,B00000000
    ,B01100000,B00000000
    ,B01100000,B00000000
    ,B00110000,B00000000
    ,B01111111,B11110000
    ,B01111111,B11110000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B01111111,B11110011
    ,B01111111,B11110011
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B01111111,B11110000
    ,B01111111,B11110000
    ,B00000000,B01100000
    ,B00000000,B00110000
    ,B00000000,B00110000
    ,B00000000,B00110000
    ,B00000000,B01110000
    ,B01111111,B11100000
    ,B01111111,B11000000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00001111,B10000000
    ,B00111111,B11100000
    ,B00110000,B01100000
    ,B01100000,B00110000
    ,B01100000,B00110000
    ,B01100000,B00110000
    ,B01100000,B00110000
    ,B00110000,B01100000
    ,B00111111,B11100000
    ,B00001111,B10000000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00000011,B10000000
    ,B00001111,B11100000
    ,B00011100,B01110000
    ,B00011001,B00110000
    ,B00110001,B00011000
    ,B00110001,B00011000
    ,B00110001,B00011000
    ,B00011001,B00110000
    ,B00011100,B01110000
    ,B00001111,B11100000
    ,B00000011,B10000000
    ,B00001111,B11100000
    ,B00011100,B01110000
    ,B00011001,B00110000
    ,B00110001,B00011000
    ,B00110111,B11011000
    ,B00110001,B00011000
    ,B00011001,B00110000
    ,B00011100,B01110000
    ,B00001111,B11100000
    ,B00000011,B10000000
 
};
static byte grafic0[20]={
  B00000000,B00000000
    ,B00000111,B11100000
    ,B00001111,B11110000
    ,B00011000,B00011000
    ,B00010000,B00001000
    ,B00010000,B00001000
    ,B00011000,B00011000
    ,B00001111,B11110000
    ,B00000111,B11100000
    ,B00000000,B00000000
};
static byte grafic1[20]={
  B00000000,B00000000
    ,B00000000,B00000000
    ,B00000000,B00100000
    ,B00000000,B00110000
    ,B00011111,B11111000
    ,B00011111,B11111000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00000000,B00000000
};
static byte grafic2[20]={
  B00000000,B00000000
    ,B00000000,B00000000
    ,B00011000,B01100000
    ,B00011100,B01110000
    ,B00010110,B00011000
    ,B00010011,B00001000
    ,B00010001,B10001000
    ,B00010000,B11111000
    ,B00010000,B01110000
    ,B00000000,B00000000
};
static byte grafic3[20]={
  B00000000,B00000000
    ,B00000000,B00000000
    ,B00001100,B00110000
    ,B00011100,B00111000
    ,B00010000,B10001000
    ,B00010000,B10001000
    ,B00010000,B10001000
    ,B00011111,B11111000
    ,B00001111,B01110000
    ,B00000000,B00000000
};
static byte grafic4[20]={
  B00000000,B00000000
    ,B00000000,B00000000
    ,B00000011,B00000000
    ,B00000011,B10000000
    ,B00000010,B11100000
    ,B00000010,B01111000
    ,B00011111,B11111000
    ,B00011111,B11111000
    ,B00000010,B00000000
    ,B00000000,B00000000
};
static byte grafic5[20]={
  B00000000,B00000000
    ,B00000000,B00000000
    ,B00001100,B11111000
    ,B00011100,B11111000
    ,B00010000,B01001000
    ,B00010000,B01001000
    ,B00011000,B11001000
    ,B00001111,B10001000
    ,B00000111,B00001000
    ,B00000000,B00000000
};
static byte grafic6[20]={
  B00000000,B00000000
    ,B00000000,B00000000
    ,B00001111,B11100000
    ,B00011111,B11110000
    ,B00011001,B10011000
    ,B00010000,B10001000
    ,B00010001,B10001000
    ,B00011111,B10011000
    ,B00001111,B00010000
    ,B00000000,B00000000
};
static byte grafic7[20]={
  B00000000,B00000000
    ,B00000000,B00000000
    ,B00000000,B00001000
    ,B00000000,B00001000
    ,B00011000,B00001000
    ,B00011111,B00001000
    ,B00000111,B11101000
    ,B00000000,B11111000
    ,B00000000,B00011000
    ,B00000000,B00000000
};
static byte grafic8[20]={
  B00000000,B00000000
    ,B00001111,B01110000
    ,B00011111,B11111000
    ,B00010000,B10001000
    ,B00010000,B10001000
    ,B00010000,B10001000
    ,B00011111,B11111000
    ,B00001111,B01110000
    ,B00000000,B00000000
    ,B00000000,B00000000
};
static byte grafic9[20]={
  B00000000,B00000000
    ,B00000000,B00000000
    ,B00001100,B11110000
    ,B00011101,B11111000
    ,B00010001,B00001000
    ,B00010001,B00001000
    ,B00011001,B10001000
    ,B00001111,B11111000
    ,B00000111,B11110000
    ,B00000000,B00000000
};
static byte grafic_W[20]={
  B00000000,B00000000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00011000,B00011000
    ,B00011000,B00011000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00000000,B00000000
    ,B00000000,B00000000
};
void setup() {
  OLED_setup(); 
  for(int i=1;i<200;i=i+2){
    data_write(grafic[i]);
  }
  for(int i=0;i<200;i=i+2){
    data_write(grafic[i]);
  }
  delay(5000);
  displayClear();
  returnHome();
 
}
 
void loop(){
  delay(100);
 
  int SS=(millis()/1000)%60;//秒
  int MM=(millis()/1000)/60%60;//分
  int HH=(millis()/1000)/60/60%24;//時
  int SSb=map(SS ,0 ,59 ,1 ,200);
  int MMb=map(MM ,0 ,59 ,1 ,200);
 
  for(int i=0;i<200;i=i+1)grafic[i]=0x00;//グラフィック変数のクリア
  for(int i=1;i<200;i=i+2){
    if(i-1<=SSb)grafic[i]|=0x03;//上に秒のバー追加
  }
  for(int i=0;i<200;i=i+2){
    if(i<=MMb)grafic[i]|=0xc0;//下に分のバー追加
  }
 
  /*----時間文字列の作成----*/
  String S = String(HH, DEC);  
  S.concat(':');
  if(MM<10)S.concat('0');
  S.concat(String(MM,DEC));
  S.concat(':');
  if(SS<10)S.concat('0');
  S.concat(String(SS,DEC));
   
  /*----時間のグラフィックマッピング----*/
  int line=180;//挿入位置 200で右端
  int k=S.length();//文字数カウント
  for(int i=k-1;i>=0;i--){
    line-=20;
    switch(S.charAt(i)){
    case '0':
      grafic_input(line,grafic0);
      break;
    case '1':
      grafic_input(line,grafic1);
      break;
    case '2':
      grafic_input(line,grafic2);
      break;
    case '3':
      grafic_input(line,grafic3);
      break;
    case '4':
      grafic_input(line,grafic4);
      break;
    case '5':
      grafic_input(line,grafic5);
      break;
    case '6':
      grafic_input(line,grafic6);
      break;
    case '7':
      grafic_input(line,grafic7);
      break;
    case '8':
      grafic_input(line,grafic8);
      break;
    case '9':
      grafic_input(line,grafic9);
      break;
    case ':':
      grafic_input(line,grafic_W);
      break;
    }
  }
  /*----表示----*/
  grafic_print(grafic);//グラフィック表示  
}
 
/*--------*/
void write4bits(uint8_t value) {
    digitalWrite(OLED_PIN_D7, (value >> 3) & 0x01);
    digitalWrite(OLED_PIN_D6, (value >> 2) & 0x01);
    digitalWrite(OLED_PIN_D5, (value >> 1) & 0x01);
    digitalWrite(OLED_PIN_D4, value & 0x01);
  pulseEnable();
}
void send(uint8_t value, uint8_t modeRS ,uint8_t modeRW) {
  digitalWrite(OLED_PIN_RS, modeRS);
  digitalWrite(OLED_PIN_RW, modeRW);
    write4bits(value>>4);
    write4bits(value);
}
void command(uint8_t value) {
  busy();
  send(value, LOW,LOW);
}
void data_write(uint8_t value) {
  busy();
  send(value,HIGH,LOW);
}
void pulseEnable() {
  digitalWrite(OLED_PIN_EN, LOW);
  delayMicroseconds(1);    
  digitalWrite(OLED_PIN_EN, HIGH);
  delayMicroseconds(1);
  digitalWrite(OLED_PIN_EN, LOW);
}
void pinModeAll(boolean mode) {
  pinMode(OLED_PIN_RS, mode);
  pinMode(OLED_PIN_RW, mode);
  pinMode(OLED_PIN_EN, mode);
  pinMode(OLED_PIN_D4, mode);
  pinMode(OLED_PIN_D5, mode);
  pinMode(OLED_PIN_D6, mode);
  pinMode(OLED_PIN_D7, mode);
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
  for(int i = 0; i < 5; i++) {
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
  command(0x01);}
void returnHome() {
  command(0x02);
}
void entryModeSet() {
  command(0x06);//Entry Mode Set [0 0 0 0 0 0 0 1 I/D S]
}
void graphicModeSet() {
  command(0x1f);//Cursor/Display Shift/Mode/Pwr[ 0 0 0 1 G/C PWR 1 1]
}
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
//{FT1:FONT TABLE SELECTION [1: 0:]} テーブル　デフォ0
//{FT0:FONT TABLE SELECTION [1: 0:]} テーブル　デフォ0
 
/*-----------*/
void OLED_setup(){//初期化
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
void OLED_Cursor(int col,int row){
  command((0x80|col));
  command((0x40|row));
}
 
void grafic_input(int col,byte *p){//表示用グラフィック書き換え
   for(int i=1;i<20;i=i+2){
    grafic[i+col]|=p[i];
  }
   for(int i=0;i<20;i=i+2){
    grafic[i+col]|=p[i];
  } 
}
 
void grafic_print(byte *p){//グラフィックを送信してのOLEDに表示
  returnHome();
for(int i=1;i<200;i=i+2){
    data_write(p[i]);
  }
  for(int i=0;i<200;i=i+2){
    data_write(p[i]);
  }
}
 
　
