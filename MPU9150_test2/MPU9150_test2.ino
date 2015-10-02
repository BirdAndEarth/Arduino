// I2C device class (I2Cdev) demonstration Arduino sketch for MPU9150
// 1/4/2013 original by Jeff Rowberg <jeff@rowberg.net> at https://github.com/jrowberg/i2cdevlib
//          modified by Aaron Weiss <aaron@sparkfun.com>
//
// Changelog:
//     2011-10-07 - initial release
//     2013-1-4 - added raw magnetometer output

/* ============================================
 I2Cdev device library code is placed under the MIT license
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ===============================================
 */

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

#define LED_PIN 13
#define DBG 1

bool blinkState = false;

int mode = 0;
long ax_ave, ay_ave, az_ave;
long gx_ave, gy_ave, gz_ave;
long ax_init, ay_init, az_init;
long gx_init, gy_init, gz_init;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(1000);
  
  
  
  
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  pinMode(LED_PIN, OUTPUT);
  
  
  
}

void loop() {
  
  SerialCheck();
  
  
  switch (mode){
  case 0: // do nothing.
    break;

  case 1: // Acc
    mode = 1;
    AveAcc(50);
    break;

  case 2: //gyro
    mode = 2;
    break;
  }
  
}

void AveAcc(int n) {
  for (int i = 1 ; i < (n + 1); i++){
    accelgyro.getAcceleration(&ax, &ay, &az);
    ax_ave += ax;
    ay_ave += ay;
    az_ave += az;
   delay(3);
  }
  ax_ave = ax_ave / n - ax_init;
  ay_ave = ay_ave / n - ay_init;
  az_ave = az_ave / n - az_init;
  //az_ave = az_ave / n;
  
  
  
  #if DBG
  Serial.print("ax_ave = "); 
  Serial.print(ax_ave);
  Serial.print("\t"); 

  Serial.print("ay_ave = "); 
  Serial.print(ay_ave);
  Serial.print("\t"); 

  Serial.print("ax_ave = "); 
  Serial.print(az_ave);
  Serial.print("\t"); 


  Serial.println("");
#endif

  
  
  
  
}


void InitAcc(int n){

    Serial.println("");
    Serial.println("INIT.....");
    Serial.println("");

  
  
  for (int i = 1 ; i < (n + 1); i++){
//    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
        accelgyro.getAcceleration(&ax, &ay, &az);

    ax_init += ax;  
    ay_init += ay;  
    az_init += az;
    
    
    delay(3);
//    gx_init += gx;  
//    gy_init += gy;  
//    gz_init += gz;
  }

  ax_init = ax_init / n;  
  ay_init = ay_init / n;  
  az_init = (az_init / n) -16383;  
//  gx_init = gx_init / n;  
//  gy_init = gy_init / n;  
//  gz_init = gz_init / n;  


#if DBG
  Serial.print("ax_init = "); 
  Serial.print(ax_init);
  Serial.print("\t"); 

  Serial.print("ay_init = "); 
  Serial.print(ay_init);
  Serial.print("\t"); 

  Serial.print("az_init = "); 
  Serial.print(az_init);
  Serial.print("\t"); 
/*
  Serial.print("gx_init = "); 
  Serial.print(gx_init);
  Serial.print("\t"); 

  Serial.print("gy_init = "); 
  Serial.print(gy_init);
  Serial.print("\t"); 

  Serial.print("gz_init = "); 
  Serial.print(gz_init);
*/
Serial.println("");
#endif
}




void InitGyro(){

}


int SerialCheck(){
  int m = 0;
  int incomingByte = 0;
  if(Serial.available()<= 0) return 0; 
  incomingByte = Serial.read();
  
  // Serial.println(incomingByte,DEC);
  
  switch (incomingByte){

  case 105: //i
    mode = 0;
    
    Serial.println("");
    Serial.println("ACC START");
    Serial.println("");
    
    InitAcc(1000);
    break;

  case 97: //a 
    mode = 1;
    break;

  case 103: //g
    mode = 2;
    break;

  case 115: //s
    mode = 0;

    Serial.println("");
    Serial.println("END");
    Serial.println("");


      break;
  }

#if DBG
//  Serial.print("Serial = ");
//  Serial.print((char)incomingByte);
//  Serial.print("\t");
//  Serial.print("mode = ");
//  Serial.print(mode);
//  Serial.println();
#endif

  return 1;

}



