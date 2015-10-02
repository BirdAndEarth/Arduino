#include <Wire.h>
#include "dv32u.h"

#define S5851_ADDR 0x48

int LED = PC7;

// unsigned char i = 0;
int ret;
extern int intTemp = 0;
int StoredData = 0;
extern float temp = 0;

void setup()
{
    pinMode(LED,OUTPUT);
    
    digitalWrite(LED,LOW);  
    Wire.begin();  
    Serial.begin(115200);
    delay(50);
    //  nameString = "--------";
}

void loop()
{ 
    tempRead();
    Serial.println(temp);
    delay(100);
    
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


// -------END of CODE--------------------------------------
