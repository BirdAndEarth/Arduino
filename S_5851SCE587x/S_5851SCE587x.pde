// SCE587x
// OSRAM SCE587x
// 
#include <Wire.h>
// #include <WString.h>
// #define maxLength 30
#include<stdio.h>

#define S5851_ADDR 0x48

//String nameString = String(maxLength);       // allocate a new String
//int characterPosition = 8;

int LOAD = 2;
int SDA  = 3;
int SCK  = 4;
int RST  = 5;

unsigned char pos=0;
// unsigned char i = 0;
int ret;
int intTemp = 0;
int StoredData = 0;

//byte opcode;
byte clumnData[7];
byte CHAR_SET[]={
//ROW0  ROW1  ROW2  ROW3  ROW4  ROW5  ROW6  ----     Hex  Dec char
  0x02, 0x06, 0x0E, 0x1E, 0x0E, 0x06, 0x02, 0x00, // 0x00   0 left triangle
  0x04, 0x00, 0x04, 0x08, 0x11, 0x11, 0x0E, 0x00, // 0x01   1 ¿
  0x1F, 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x00, // 0x02   2 x bar
  0x1F, 0x00, 0x11, 0x19, 0x15, 0x13, 0x11, 0x00, // 0x03   3 N bar
  0x1F, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11, 0x00, // 0x04   4 n bar
  0x00, 0x00, 0x0D, 0x12, 0x12, 0x12, 0x0D, 0x00, // 0x05   5 α
  0x0C, 0x12, 0x12, 0x16, 0x11, 0x16, 0x10, 0x00, // 0x06   6 β
  0x06, 0x08, 0x04, 0x0E, 0x11, 0x11, 0x0E, 0x00, // 0x07   7 δ
  0x00, 0x00, 0x00, 0x04, 0x0A, 0x11, 0x1F, 0x00, // 0x08   8 Δ
  0x00, 0x10, 0x1C, 0x12, 0x12, 0x02, 0x01, 0x00, // 0x09   9 η
  0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x0E, 0x00, // 0x0A  10 θ
  0x00, 0x10, 0x08, 0x04, 0x0A, 0x11, 0x11, 0x00, // 0x0B  11 λ
  0x00, 0x00, 0x09, 0x09, 0x09, 0x0E, 0x10, 0x00, // 0x0C  12 μ
  0x00, 0x01, 0x0E, 0x1A, 0x0A, 0x0A, 0x0A, 0x00, // 0x0D  13 π
  0x00, 0x00, 0x0F, 0x12, 0x12, 0x12, 0x0C, 0x00, // 0x0E  14 σ
  0x1F, 0x08, 0x04, 0x02, 0x04, 0x08, 0x1F, 0x00, // 0x0F  15 Σ
  0x00, 0x00, 0x01, 0x0E, 0x14, 0x04, 0x04, 0x00, // 0x10  16 τ
  0x00, 0x04, 0x0E, 0x15, 0x15, 0x0E, 0x04, 0x00, // 0x11  17 φ
  0x0E, 0x11, 0x11, 0x11, 0x11, 0x0A, 0x1B, 0x00, // 0x12  18 Ω
  0x04, 0x00, 0x0E, 0x11, 0x1F, 0x11, 0x11, 0x00, // 0x13  19 Å
  0x04, 0x00, 0x0E, 0x12, 0x12, 0x12, 0x0D, 0x00, // 0x14  20 å
  0x0A, 0x00, 0x0E, 0x11, 0x1F, 0x11, 0x11, 0x00, // 0x15  21 Ä
  0x0A, 0x00, 0x0E, 0x12, 0x12, 0x12, 0x0D, 0x00, // 0x16  22 ä
  0x0A, 0x0E, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00, // 0x17  23 Ö
  0x0A, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00, // 0x18  24 ö
  0x0A, 0x00, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00, // 0x19  25 Ü
  0x00, 0x0A, 0x00, 0x11, 0x11, 0x11, 0x0E, 0x00, // 0x1A  26 ü
  0x00, 0x04, 0x02, 0x1F, 0x02, 0x04, 0x00, 0x00, // 0x1B  27 right arrow
  0x00, 0x0F, 0x08, 0x08, 0x08, 0x18, 0x08, 0x00, // 0x1C  28 root
  0x0C, 0x12, 0x04, 0x08, 0x1E, 0x00, 0x00, 0x00, // 0x1D  29 square
  0x06, 0x09, 0x08, 0x1C, 0x08, 0x08, 0x1F, 0x00, // 0x1E  30 Pond
  0x11, 0x0A, 0x04, 0x04, 0x0E, 0x04, 0x04, 0x00, // 0x1F  31 Yen
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x20  32 Space
  0x00, 0x04, 0x04, 0x04, 0x04, 0x00, 0x04, 0x00, // 0x21  33 !
  0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x22  34 "
  0x0A, 0x0A, 0x1F, 0x0A, 0x1F, 0x0A, 0x0A, 0x00, // 0x23  35 #
  0x04, 0x0F, 0x14, 0x0E, 0x05, 0x1E, 0x04, 0x00, // 0x24  36 $
  0x18, 0x19, 0x02, 0x04, 0x08, 0x13, 0x03, 0x00, // 0x25  37 %
  0x08, 0x14, 0x14, 0x08, 0x15, 0x12, 0x0D, 0x00, // 0x26  38 &
  0x0C, 0x0C, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, // 0x27  39 '
  0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x02, 0x00, // 0x28  40 (
  0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x00, // 0x29  41 )
  0x00, 0x0A, 0x04, 0x1F, 0x04, 0x0A, 0x00, 0x00, // 0x2A  42 *
  0x00, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x00, 0x00, // 0x2B  43 +
  0x00, 0x00, 0x00, 0x18, 0x18, 0x08, 0x10, 0x00, // 0x2C  44 ,
  0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, // 0x2D  45 -
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00, // 0x2E  46 .
  0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x00, 0x00, // 0x2F  47 /
  0x0E, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0E, 0x00, // 0x30  48 0
  0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00, // 0x31  49 1
  0x0E, 0x11, 0x01, 0x06, 0x08, 0x10, 0x1F, 0x00, // 0x32  50 2
  0x0E, 0x11, 0x01, 0x0E, 0x01, 0x11, 0x0E, 0x00, // 0x33  51 3
  0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02, 0x00, // 0x34  52 4
  0x1F, 0x10, 0x1E, 0x01, 0x01, 0x01, 0x1E, 0x00, // 0x35  53 5
  0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E, 0x00, // 0x36  54 6
  0x1F, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08, 0x00, // 0x37  55 7
  0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E, 0x00, // 0x38  56 8
  0x0E, 0x11, 0x11, 0x0F, 0x01, 0x02, 0x0C, 0x00, // 0x39  57 9
  0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x00, 0x00, // 0x3A  58 :
  0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x04, 0x08, 0x00, // 0x3B  59 ;
  0x01, 0x02, 0x04, 0x08, 0x04, 0x02, 0x01, 0x00, // 0x3C  60 <
  0x00, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x00, 0x00, // 0x3D  61 =
  0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x00, // 0x3E  62 >
  0x0E, 0x11, 0x01, 0x02, 0x04, 0x00, 0x04, 0x00, // 0x3F  63 ?
  0x0E, 0x11, 0x17, 0x15, 0x17, 0x10, 0x0E, 0x00, // 0x40  64 @
  0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00, // 0x41  65 A
  0x1E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x1E, 0x00, // 0x42  66 B
  0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E, 0x00, // 0x43  67 C
  0x1E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1E, 0x00, // 0x44  68 D
  0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x1F, 0x00, // 0x45  69 E
  0x1E, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x10, 0x00, // 0x46  70 F
  0x0E, 0x11, 0x10, 0x10, 0x13, 0x11, 0x0E, 0x00, // 0x47  71 G
  0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00, // 0x48  72 H
  0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00, // 0x49  73 I
  0x01, 0x01, 0x01, 0x01, 0x01, 0x11, 0x0E, 0x00, // 0x4A  74 J
  0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11, 0x00, // 0x4B  75 K
  0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x00, // 0x4C  76 L
  0x11, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x11, 0x00, // 0x4D  77 M
  0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11, 0x00, // 0x4E  78 N
  0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00, // 0x4F  79 O
  0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10, 0x10, 0x00, // 0x50  80 P
  0x0E, 0x11, 0x11, 0x11, 0x15, 0x12, 0x0D, 0x00, // 0x51  81 Q
  0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11, 0x00, // 0x52  82 R
  0x0E, 0x11, 0x10, 0x0E, 0x01, 0x11, 0x0E, 0x00, // 0x53  83 S
  0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, // 0x54  84 T
  0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00, // 0x55  85 U
  0x11, 0x11, 0x11, 0x0A, 0x0A, 0x04, 0x04, 0x00, // 0x56  86 V
  0x11, 0x11, 0x11, 0x15, 0x15, 0x1B, 0x11, 0x00, // 0x57  87 W
  0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11, 0x00, // 0x58  88 X
  0x11, 0x11, 0x0A, 0x04, 0x04, 0x04, 0x04, 0x00, // 0x59  89 Y
  0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1F, 0x00, // 0x5A  90 Z
  0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x00, // 0x5B  91 [
  0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, // 0x5C  92 BackSpace
  0x1C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x1C, 0x00, // 0x5D  93 ]
  0x04, 0x0A, 0x15, 0x04, 0x04, 0x04, 0x04, 0x00, // 0x5E  94 UpArrow
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, // 0x5F  95 _
  0x0C, 0x0C, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, // 0x60  96 `
  0x00, 0x00, 0x0E, 0x12, 0x12, 0x12, 0x0D, 0x00, // 0x61  97 a
  0x10, 0x10, 0x10, 0x16, 0x19, 0x11, 0x1E, 0x00, // 0x62  98 b
  0x00, 0x00, 0x0E, 0x10, 0x10, 0x11, 0x0E, 0x00, // 0x63  99 c
  0x01, 0x01, 0x01, 0x0D, 0x13, 0x11, 0x0F, 0x00, // 0x64 100 d
  0x00, 0x00, 0x0E, 0x11, 0x1E, 0x10, 0x0E, 0x00, // 0x65 101 e
  0x04, 0x0A, 0x08, 0x1C, 0x08, 0x08, 0x08, 0x00, // 0x66 102 f
  0x00, 0x00, 0x0F, 0x11, 0x0F, 0x01, 0x06, 0x00, // 0x67 103 g
  0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x11, 0x00, // 0x68 104 h
  0x00, 0x04, 0x00, 0x0C, 0x04, 0x04, 0x0E, 0x00, // 0x69 105 i
  0x02, 0x00, 0x06, 0x02, 0x02, 0x12, 0x0C, 0x00, // 0x6A 106 j
  0x10, 0x10, 0x12, 0x14, 0x18, 0x14, 0x12, 0x00, // 0x6B 107 k
  0x0C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00, // 0x6C 108 l
  0x00, 0x00, 0x0A, 0x15, 0x11, 0x11, 0x11, 0x00, // 0x6D 109 m
  0x00, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11, 0x00, // 0x6E 110 n
  0x00, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00, // 0x6F 111 o
  0x00, 0x00, 0x1E, 0x11, 0x19, 0x16, 0x10, 0x00, // 0x70 112 p
  0x00, 0x00, 0x0F, 0x11, 0x13, 0x0D, 0x01, 0x00, // 0x71 113 q
  0x00, 0x00, 0x0B, 0x0C, 0x08, 0x08, 0x08, 0x00, // 0x72 114 r
  0x00, 0x00, 0x0E, 0x10, 0x0E, 0x01, 0x1E, 0x00, // 0x73 115 s
  0x08, 0x08, 0x1C, 0x08, 0x08, 0x0A, 0x04, 0x00, // 0x74 116 t
  0x00, 0x00, 0x11, 0x11, 0x11, 0x13, 0x0D, 0x00, // 0x75 117 u
  0x00, 0x00, 0x11, 0x11, 0x11, 0x0A, 0x04, 0x00, // 0x76 118 v
  0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0A, 0x00, // 0x77 119 w
  0x00, 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x00, // 0x78 120 x
  0x00, 0x00, 0x11, 0x0A, 0x04, 0x04, 0x08, 0x00, // 0x79 121 y
  0x00, 0x00, 0x1F, 0x02, 0x04, 0x08, 0x1F, 0x00, // 0x7A 122 z
  0x02, 0x04, 0x04, 0x08, 0x04, 0x04, 0x02, 0x00, // 0x7B 123 {
  0x04, 0x04, 0x04, 0x00, 0x04, 0x04, 0x04, 0x00, // 0x7C 124 |
  0x08, 0x04, 0x04, 0x02, 0x04, 0x04, 0x08, 0x00, // 0x7D 125 }
  0x00, 0x00, 0x08, 0x15, 0x02, 0x00, 0x00, 0x00, // 0x7E 126 ~
  0x0A, 0x15, 0x0A, 0x15, 0x0A, 0x15, 0x0A, 0x00  // 0x7F 127 CheckerPattern
};

void setup()
{
  pinMode(LOAD,OUTPUT);
  pinMode(SDA,OUTPUT);
  pinMode(SCK,OUTPUT);
  pinMode(RST,OUTPUT);
  
  digitalWrite(RST,LOW);  
  digitalWrite(LOAD,HIGH);
  digitalWrite(SDA,LOW);
  digitalWrite(SCK,HIGH);
  digitalWrite(RST,HIGH);
  Wire.begin();  
  Serial.begin(115200);
  delay(500);
//  nameString = "--------";

}

void loop()
{ 
  // temp read ///////////////
  int time = 0;  
  int n = 0;
/*
    while(1){
      time = millis();
      if(time % 500 == 0){
        tempRead();
        //dispLed(intTemp);
        break;
      }else{     
        //dispLed(intTemp);
      }
   }
*/
  // Disp SCE587x ////////////  
//  int k = 0;
  Clear();

/*  
  for(int k = 0; k < 16; k++){
    for(int i = 0; i < 8; i++){
      SetChar(i);
      for(int j=0;j<7;j++){
        clumnData[j] = CHAR_SET[((k * 8 + i) << 3) + j];
      }
      ColData(clumnData);

    }
*/

  char test[8];
  int a = 999;
  sprintf(test,"%d",a);
  for(int i = 0; i < 8; i++){
    DispChar(i,test[i]);
  }

  
  Serial.println(test);
  SetBrightness(6);
  delay(100);
  SetBrightness(7);
  delay(10);
 
}
// S-5851  ////////////////////////////////////////////////////
void tempRead()
{
  int data1=0;
  int data2=0;
  int data=0;
  float temp = 0;

  //Dummy Write
  Wire.beginTransmission(S5851_ADDR);
  Wire.send(0x00);
 
  //Read Data 
  ret=Wire.requestFrom(S5851_ADDR, 2);
  if (Wire.available()) {
    data1 = Wire.receive();
    data2 = Wire.receive();

    data1= data1 << 8;
    data = data1 + data2;
    data = data >> 4;
    temp = data*0.0625;

    //data = temp * 10;
     
    StoredData = data;
    intTemp = data;    
  } else {
    intTemp=999; 
  }
  ret=Wire.endTransmission();
}



// SCE5870 ////////////////////////////////////////////////////
// Software Reset
void Clear()
{
  sendData(0xC0, 0x00);
}

// Set Brightness
void SetBrightness(byte Brightness)
{
  sendData(0xE0, Brightness);
}

void DispChar(int No, char c){
  int k;
  k = (int)c;
  SetChar((byte)No);
  Serial.print(c);
  Serial.println(k);
  char uniChar[1];
      SetChar(No);
      for(int j=0;j<7;j++){
        clumnData[j] = CHAR_SET[(k << 3) + j];
      }
      ColData(clumnData);
}


// Send Char No
void SetChar(byte No)
{
  sendData(0xA0, No);
}

// Send Column Data
void ColData(byte Data[])
{
  for(int i=0;i<7;i++){
    sendData(0x00, Data[i]);  
  }
    //Serial.println("");
}

// ---------------------------------------------------
void sendData(byte OPCODE, byte DATA)
{
  digitalWrite(LOAD,LOW);
  //Send 5bit data
  for(int i=0;i<5;i++){
    digitalWrite(SCK,LOW);
    digitalWrite(SDA, (DATA >> i) & 0x01);
    digitalWrite(SCK,HIGH);
  }
  //Send OPCODE
  for(int i=5;i<8;i++){
    digitalWrite(SCK,LOW);  
    digitalWrite(SDA, (OPCODE >> i) & 0x01);
    digitalWrite(SCK,HIGH);
  }
  //Send LOAD
  digitalWrite(LOAD,HIGH);
  for(int i=0;i<3;i++){
    digitalWrite(SCK,LOW);  
    digitalWrite(SCK,HIGH);
  }
}
// -------END of CODE--------------------------------------
