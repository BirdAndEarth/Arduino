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


#define LED_PIN 13

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
int16_t ax,ay,az;
int16_t gx,gy,gz;
int16_t mx,my,mz;

boolean blinkState = false;
int mode = 0;
long ax_ave, ay_ave, az_ave;
long gx_ave, gy_ave, gz_ave;
long ax_init, ay_init, az_init;
long gx_init, gy_init, gz_init;

void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  // initialize serial communication
  // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
  // it's really up to you depending on your project)
  Serial.begin(115200);

  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  // configure Arduino LED for
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // read raw accel/gyro measurements from device
  accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);

  // these methods (and a few others) are also available
  //accelgyro.getAcceleration(&ax, &ay, &az);
  //accelgyro.getRotation(&gx, &gy, &gz);

  // display tab-separated accel/gyro x/y/z values




  accelgyro.getRotation(&gx, &gy, &gz);
  Serial.print(gx); 
  Serial.print("\t");
  Serial.print(gy); 
  Serial.print("\t");
  Serial.print(gz); 
  Serial.print("\t");
  Serial.println("");

  delay(10);




  /* 
   
   
   Serial.print("a/g/m:\t");
   Serial.print(ax); Serial.print("\t");
   Serial.print(ay); Serial.print("\t");
   Serial.print(az); Serial.print("\t");
   Serial.print(gx); Serial.print("\t");
   Serial.print(gy); Serial.print("\t");
   Serial.print(gz); Serial.print("\t");
   Serial.print(mx); Serial.print("\t");
   Serial.print(my); Serial.print("\t");
   Serial.println(mz);
   
   // blink LED to indicate activity
   blinkState = !blinkState;
   digitalWrite(LED_PIN, blinkState);
   
   
   */





  switch (mode){
  case: 
    0 // do nothing.
    break;

  case: 
    1 // Acc
    mode = 1;
    break;

  case: 
    2 //gyro
    mode = 2;
    break;
  }
}


void AveAcc(int n, ) {
  for (int i = 1 ; i < (n + 1); i++){
    accelgyro.getAcceleration(&ax, &ay, &az);
    ax_ave += ax;
    ay_ave += ay;
    az_ave += az;
  }
  ax_ave = ax_ave / n;
  ay_ave = ay_ave / n;
  az_ave = az_ave / n;
}


void InitAcc(int n){

  for (int i = 1 ; i < (n + 1); i++){
    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    ax_init += ax;  
    ay_init += ay;  
    az_init += az;
    gx_init += gx;  
    gy_init += gy;  
    gz_init += gz;
  }

  ax_init = ax_init / n;  
  ay_init = ay_init / n;  
  az_init = az_init / n;  
  gx_init = gx_init / n;  
  gy_init = gy_init / n;  
  gz_init = gz_init / n;  


#if DBG
  Serial.print("ax_init = "); 
  Serial.print("\t"); 
  Serial.print(ax_init);
  Serial.print("ay_init = "); 
  Serial.print("\t"); 
  Serial.print(ay_init);
  Serial.print("ax_init = "); 
  Serial.print("\t"); 
  Serial.print(az_init);
  Serial.print("gx_init = "); 
  Serial.print("\t"); 
  Serial.print(gx_init);
  Serial.print("gy_init = "); 
  Serial.print("\t"); 
  Serial.print(gy_init);
  Serial.print("gz_init = "); 
  Serial.print("\t"); 
  Serial.print(gz_init);
  Serial.println("");
#endif
}




void InitGyro(){

}


int SerialCheck(){
  int m = 0;
  char incomingByte = 0;
  if(Serial.available()<= 0) return 0; 

  incomingByte = Serial.read();

  switch (incomingByte){


  case: 
    "i"
      mode = 0;


    break;

  case: 
    "a"
      mode = 1;
    break;

  case: 
    "g"
      mode = 2;
    break;

  case: 
    "s"
      mode = 0
      break;



  }




  return 1;
}





































