
int interval = 500;
String strRead;
int sensorStates[4] = {0, 0, 0, 0};
boolean blinkFlg = false;
int sensorNo[4] = {
  18, 19, 20, 21
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);

}

void loop() {
  checkSerial();
  checkInterval();
}

void checkSerial() {

  serialReadLineCheck();
  strRead = serialReadLine();
  String body;

  if (strRead.length() > 0) {
    String header = strRead.substring(0, 1);
    if (strRead.length() > 2) {
      body = strRead.substring(2);
    }

    if (header == "i") {
      interval = body.substring(0, 3).toInt();
      Serial.println(interval);
    }
    else if (0 <= header.toInt() && header.toInt() <= 8 ) {
      int num = header.toInt();
      Serial.println(header);
      if (1 <= num &&  num <= 4) {
        if      (sensorStates[num - 1] == 0) {
          sensorStates[num - 1] = 1;
        }
        else if (sensorStates[num - 1] == 1) {
          sensorStates[num - 1] = 0;
        }        
        else if (sensorStates[num - 1] == 2) {
          sensorStates[num - 1] = 1;
        }
      }
      else if (5 <= num &&  num <= 8) {
        if      (sensorStates[num - 5] == 0) {
          sensorStates[num - 5] = 2;
        }
        else if (sensorStates[num - 5] == 1) {
          sensorStates[num - 5] = 2;
        }
        else if (sensorStates[num - 5] == 2) {
          sensorStates[num - 5] = 0;
        }
      }

//      Serial.print(sensorStates[0]);
//      Serial.print(sensorStates[1]);
//      Serial.print(sensorStates[2]);
//      Serial.println(sensorStates[3]);

    }
  }
}




void checkInterval() {
  static boolean fflg = false;
  unsigned long currentMillis = millis();
  static unsigned long previousMillis;
  if (currentMillis - previousMillis >= interval) {
    blinkFlg = !blinkFlg;
    changeLedState();
    previousMillis = currentMillis;

//    Serial.print(sensorStates[0]);
//    Serial.print(sensorStates[1]);
//    Serial.print(sensorStates[2]);
//    Serial.println(sensorStates[3]);



    //    Serial.println(previousMillis);





  }
}

void changeLedState() {

  for (int i = 0; i < 4; i++) {
    if (sensorStates[i] == 0) {
      digitalWrite(sensorNo[i], HIGH);
    }
    else if (sensorStates[i] == 1) {
      digitalWrite(sensorNo[i], LOW);
    }
    else if (sensorStates[i] == 2) {
      digitalWrite(sensorNo[i], blinkFlg);
    }
  }
}



//-Serial--------------------------------------
String _strRead, _strBuf;
int _readFlg = 0;

void serialReadLineCheck(void) {
  while (Serial.available()) {
    delay(3);  //delay to allow buffer
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

