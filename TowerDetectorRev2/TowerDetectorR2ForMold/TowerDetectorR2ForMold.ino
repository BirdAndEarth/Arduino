/*************************************
 * TowerDetector for SmArt!Box       
 *   FOR MOLD 3 LIGHT              
 *  15/01/28  Rev.1.0  shiu  New.    
 *  15/01/28  Rev.2.0  shiu  add WatiMode.
 *************************************/
#include "dv32u.h"
#include <SHT2x.h>
#include <Wire.h>

String PVER = "2.0";
String PNAME = "TD_Mold";
String DELIMITER = ":";

#define NORMAL_MODE 0
#define ANSWER_MODE 1
#define RAWDAT_MODE 2
#define ANSTOW_MODE 3
#define ANSSHT_MODE 4
#define WAIT___MODE 5


const int SENSORS = 4;
boolean sensorStateNow[SENSORS] = {0, 0, 0, 0};
boolean sensorStateOld[SENSORS] = {1, 1, 1, 1};
int sensorThreshold[SENSORS] = {
  150, 150, 150, 150
};
int sensorValue[SENSORS];
int sensorNo[SENSORS] = {
//    18, 19, 20, 21
    21, 18, 19, 20 // for Mold   
};
float humi = 0;
float temp = 0;
int mode = WAIT___MODE;

String inString = "";
String strRead;

long tinter = 100;
long sinter = 1000;
long rinter = 100;
long timeNow = 0;

long ttimeOld = 0;
long stimeOld = 0;
long rtimeOld = 0;

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  while (!Serial);
  
  //For Mold
  pinMode(21,OUTPUT);
  digitalWrite(21, LOW);
}

void loop()
{
  serialReadLineCheck();
  strRead = serialReadLine();
  String body;
  if (strRead.length() > 0) {
    String header = strRead.substring(0, 1);
    if (strRead.length() > 2) {
      body = strRead.substring(2);
    }

    if (header == "?") {
      mode = ANSWER_MODE;
    }

    else if (header == "r") {
      mode = RAWDAT_MODE;
    }

    else if (header == "n") {
      mode = NORMAL_MODE;
    }

    else if (header == "t") {
      mode = ANSTOW_MODE;
    }

    else if (header == "w") {
      mode = WAIT___MODE;
    }

    else if (header == "s") {
      mode = ANSSHT_MODE;
    }





    else if (header == "z") {
      sensorThreshold[0] = body.substring(0, 3).toInt();
      sensorThreshold[1] = body.substring(3, 6).toInt();
      sensorThreshold[2] = body.substring(6, 9).toInt();
      sensorThreshold[3] = body.substring(9, 12).toInt();
    }

    else if (header == "q") {
      String str = "q:";
      for (int i = 0; i < SENSORS; i++) {
        str += sensorThreshold[i];
        if (i != (SENSORS - 1)) {
          str += ":";
        }
      }
      Serial.println(str);
    }
  }

  switch (mode) {
    case ANSWER_MODE:
      AnswerName();
      mode = NORMAL_MODE;
      break;

    case WAIT___MODE:
      break;

    case RAWDAT_MODE:
      RawDataMode();
      mode = NORMAL_MODE;
      break;

    case NORMAL_MODE:
      //mode = NORMAL_MODE;
      NormalMode();
      // Do nothing...
      break;

    case ANSTOW_MODE:
      AnswerTower();
      mode = NORMAL_MODE;
      break;

    case ANSSHT_MODE:
      AnswerSHT();
      mode = NORMAL_MODE;
      break;

  }
}

//---------------------------------------------

void NormalMode() {
  timeNow = millis();
  if (timeNow - ttimeOld > tinter) {
    checkSensorState();
    ttimeOld = timeNow;
  }

  //  if (timeNow - stimeOld > sinter) {
  //    AnswerSHT();
  //    stimeOld = timeNow;
  //  }

}


void RawDataMode()
{
  timeNow = millis();
  if (timeNow - rtimeOld > rinter) {
    checkSensorStateRaw();
    rtimeOld = timeNow;
  }
}

void RawDataContMode()
{
  timeNow = millis();
  if (timeNow - rtimeOld > rinter) {
    checkSensorStateRaw();
    rtimeOld = timeNow;
  }
}

void checkSensorState() {
  int checker = 0;
  _updateSensorState();
  for (int i = 0; i < SENSORS; i++) {
    if (sensorStateNow[i] != sensorStateOld[i]) {
      checker += 1;
      sensorStateOld[i] = sensorStateNow[i];
    }
  }
  if (checker > 0) {
    _printSensor();
  }
}
void _updateSensorState() {
  String s;
  for (int i = 0; i < SENSORS; i++) {
    sensorValue[i] = analogRead(sensorNo[i]);
    //    s += String(sensorValue[i]) + " ";
    sensorStateNow[i] = false;
    if (sensorValue[i] > sensorThreshold[i]) {
      sensorStateNow[i] = true;
    }
  }
  //  Serial.println(s);

}
void _printSensor() {
  String str = "t:";
  for (int i = 0; i < SENSORS; i++) {
    if (sensorStateNow[i]) {
      str += "1";
    }
    else {
      str += "0";
    }

    if (i != (SENSORS - 1)) {
      str += ":";
    }
  }
  Serial.println(str);
}

void checkSensorStateRaw() {
  int checker = 0;
  _updateSensorState();
  _printSensorRaw();
}

void _printSensorRaw() {
  String str = "r:";
  for (int i = 0; i < SENSORS; i++) {

    char cs[16];
    int sv = sensorValue[i];
    String(sv).toCharArray(cs, 5);
    sprintf(cs, "%3d", sv);
    str += String(cs);
    if (i != (SENSORS - 1)) {
      str += ":";
    }
  }
  str += "\t";
  for (int i = 0; i < SENSORS; i++) {
    str += sensorThreshold[i];
    if (i != (SENSORS - 1)) {
      str += ":";
    }
  }
  str += "\t";
  for (int i = 0; i < SENSORS; i++) {
    str += sensorStateNow[i];
    if (i != (SENSORS - 1)) {
      str += ":";
    }
  }
  str += "\t";
  Serial.println(str);
}

void UpdateSHT() {
  humi = SHT2x.GetHumidity();
  temp = SHT2x.GetTemperature();
}

void AnswerName()
{
  Serial.println("?:" + PNAME + DELIMITER + PVER);
}

void AnswerTower()
{
  checkSensorState();
  _printSensor();
}

void AnswerSHT()
{
  //  String ans = "s:" + temp + "," + humi;
  UpdateSHT();
  Serial.println("s:" + String(temp) + ":" + String(humi));
}


//-Serial--------------------------------------
String _strRead, _strBuf;
int _readFlg = 0;

void serialReadLineCheck(void) {
  while (Serial.available()) {
    //delay(3);  //delay to allow buffer
    if (Serial.available() > 0) {
      char c = Serial.read();  //gets one byte from serial buffer
      if ((_readFlg == 0) && ((c == '\r') || (c == '\n'))) {
        _strRead = _strBuf;
        _strBuf = "";
        _readFlg = 1;
      }
      else if ((_readFlg == 1) && ((c == '\r') || (c == '\n'))) {
        //do nothing
      }
      else {
        _strBuf += c;
      }
    }
  }
}

String serialReadLine(void) {
  String s = "";
  if (_readFlg) {
    s = _strRead; //see what was received
    _strRead = "";
    _readFlg = 0;
  }
  return s;
}

//-END OF CODE-------------------------------





