#include <Wire.h>


#define S5851_ADDR 0x48

int CLEAR = 5;
int SRCLK = 4;
int RCLK  = 3;
int SER   = 2;

unsigned char pos=0;
// unsigned char i = 0;
int ret;
int intTemp = 0;
int StoredData = 0;

void setup()
{
  pinMode(CLEAR,OUTPUT);
  pinMode(SRCLK,OUTPUT);
  pinMode(RCLK,OUTPUT);
  pinMode(SER,OUTPUT);

  digitalWrite(CLEAR,LOW);  
  digitalWrite(SRCLK,LOW);
  digitalWrite(RCLK,LOW);
  digitalWrite(SER,LOW);
  Wire.begin();  
  Serial.begin(115200);
  delay(50);
  //  nameString = "--------";
}

void loop()
{ 
  // temp read ///////////////
  int time = 0;  
  int i = 0;

  for(i = 1; i<=16; i++){
    setSR(i);
    tempRead();
    Serial.print(i);
    Serial.print(":");

    Serial.print(intTemp);
    Serial.println("");
    
    //Serial.print(",");
  }
    Serial.println("");

  delay(1000);

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
  Wire.write(0x00);

  //Read Data 
  ret=Wire.requestFrom(S5851_ADDR, 2);
  if (Wire.available()) {
    data1 = Wire.read();
    data2 = Wire.read();

    data1= data1 << 8;
    data = data1 + data2;
    data = data >> 4;
    temp = data*0.0625;

    //data = temp * 10;

    StoredData = data;
    intTemp = data;    
  } 
  else {
    intTemp=999; 
  }
  ret=Wire.endTransmission();
}

// S-5851  ////////////////////////////////////////////////////
void clearSR(){
  digitalWrite(CLEAR,LOW);
}

void setSR(int DUT){


  //0
  digitalWrite(CLEAR,LOW);
  digitalWrite(SRCLK,LOW);
  digitalWrite(SRCLK,LOW);
  digitalWrite(SER,LOW);
  delayMicroseconds(5);

  //1
  digitalWrite(SRCLK,LOW);
  digitalWrite(CLEAR,HIGH);
  digitalWrite(SER,HIGH);
  delayMicroseconds(5);

  //1

  //   Serial.print("DUT=");
  //   Serial.println(DUT);

  for(int i=1; i <= DUT; i++){ 
    digitalWrite(SRCLK,HIGH);
    delayMicroseconds(5);
    digitalWrite(SER,LOW);
    digitalWrite(SRCLK,LOW);
    delayMicroseconds(5);
    //    Serial.println("INLOOP");
  }
  //    Serial.println("OUTLOOP");


  digitalWrite(RCLK,HIGH);
  delayMicroseconds(5);
  digitalWrite(RCLK,LOW);
  delayMicroseconds(500);
}

// -------END of CODE--------------------------------------







