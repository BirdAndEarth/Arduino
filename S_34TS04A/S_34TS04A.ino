#include <Wire.h>

#define S34TS04A_ADDR B0011000
#define DBG 0

int CLEAR = 5;
int SRCLK = 4;
int RCLK  = 3;
int SER   = 2;


unsigned char pos=0;
// unsigned char i = 0;
int ret1 = 0;
int ret2 = 0;
int ret3 = 0;
int ret4 = 0;
int ret5 = 0;
int ret6 = 0;
int ret7 = 0;

int OutPin = 9;
int pwmOutValue = 0;


int intTemp = 0;
int StoredData = 0;

void setup()
{
  pinMode(CLEAR,OUTPUT);
  pinMode(SRCLK,OUTPUT);
  pinMode(RCLK,OUTPUT);
  pinMode(SER,OUTPUT);
  pinMode(10,OUTPUT);


  digitalWrite(CLEAR,LOW);  
  digitalWrite(SRCLK,LOW);
  digitalWrite(RCLK,LOW);
  digitalWrite(SER,LOW);
  Wire.begin();  
  Serial.begin(115200);
  delay(50);
  setupTS();

  //  nameString = "--------";
}

void loop()
{ 
  // temp read ///////////////
  int time = 0;  

  tempRead();




  pwmOutValue = map((long)intTemp, 1040, 1440, 0, 255);
  
  
  
  
  
  
  
  analogWrite(10,pwmOutValue);
  Serial.print("intTEMP = ");
  Serial.print(intTemp);
  Serial.print(" pwm = ");
  Serial.println(pwmOutValue);




  delay(1000);

}
// ----- end of main -------------------


/*---------------------------------------
 S-34TS04A 
 ----------------------------------------*/

void tempRead()
{
  unsigned int  data1=0;
  unsigned int   data2=0;
  unsigned int  data=0;


  float temp = 0;

#if DBG
  Serial.println("  tempRead Start: ");
#endif

  ret1 = 0;
  ret2 = 0;
  ret3 = 0;
  ret4 = 0;
  ret5 = 0;
  ret6 = 0;
  ret7 = 0;
  // 1. TS Shutdownmode set
  Wire.beginTransmission(S34TS04A_ADDR);
  Wire.write(0x01);
  Wire.write(0x01);
  Wire.write(0x00);
  ret1=Wire.endTransmission();


  // 2. Resolution
  Wire.beginTransmission(S34TS04A_ADDR);
  Wire.write(0x08);
  Wire.write(0x00);
  Wire.write(B00000011);
  ret2=Wire.endTransmission();


  // 3. TS Shutdown mode release
  Wire.beginTransmission(S34TS04A_ADDR);
  Wire.write(0x01);
  Wire.write(0x00);
  Wire.write(0x00);
  ret3=Wire.endTransmission();



  // 4. wait 100ms
  delay(100);



#if DBG
  Serial.print("  1. =");
  Serial.println(ret1);

  Serial.print("  2. =");
  Serial.println(ret2);

  Serial.print("  3. =");
  Serial.println(ret3);
#endif

  // 5. Ambient Temprature Read
  Wire.beginTransmission(S34TS04A_ADDR);
  Wire.write(B00000101);
  ret4=Wire.endTransmission(false);

  ret5=Wire.requestFrom(S34TS04A_ADDR, 2);
  if (Wire.available()) {
    data1 = Wire.read();
    data2 = Wire.read();
    ret3=Wire.endTransmission();


    data1 = data1 & 0x1F;
    data1= data1 << 8;
    data = data1 + data2;
    temp = data*0.0625;

    //data = temp * 10;

    StoredData = data;
    intTemp = data;    
  } 
  else {
    intTemp=999; 
  }

#if DBG
  Serial.print("  4. =");
  Serial.println(ret4);
  Serial.print("  5. =");
  Serial.println(ret5);
  Serial.print("  data1 = ");
  Serial.print(data1, BIN);
  Serial.print("  data2 = ");
  Serial.println(data2, BIN);
#endif

}


void setupTS(){
}





// -------END of CODE--------------------------------------




















