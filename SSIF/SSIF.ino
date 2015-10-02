/*************************************
 * SSIF for DB
 *  15/09/11  Rev.0.0  shiu  New.
 *************************************/
#include "dv32u.h"

String PVER = "0.0";
String PNAME = "SSIF";
String DELIMITER = ":";

int Sr700ReadPin = PD6;
int Sr700NothingPin = PD7;
int Sr700OkPin  = PF7;
int Sr700NgPin  = PF6;
int Sr700ErrorPin  = PF5;
int Sr700BusyPin  = PF4;


int dbIn1Pin = PB0; // IN1
int dbIn2Pin = PB1; // IN2
int dbIn3Pin = PB2; // IN3
int dbIn4Pin = PB3; // IN4

int startPin    = dbIn1Pin;
int lotClearPin = dbIn2Pin;

int dbOut1Pin = PB4; // OUT1
int dbOut2Pin = PB5; // OUT2
int dbOut3Pin = PB6; // OUT3
int dbOut4Pin = PB7; // OUT4

int busyPin = dbOut1Pin;
int okPin   = dbOut2Pin;
int ngPin   = dbOut3Pin;




//int testPin = PD3;



String strSerialIncomingSsif;
String strSerialIncomingSr700;

const long interval = 1000;           // interval at which to blink (milliseconds)
unsigned long previousMillis = 0;        // will store last time LED was updated
int ledState = LOW;             // ledState used to set the LED


const long Sr700CodeReadInterval = 1000;
unsigned long Sr700CodeReadPreviousMillis = 0;        // will store last time LED was updated




const long busyInterval = 1000;
int busyOldState = LOW;






void setup()
{

  pinMode(Sr700ReadPin, OUTPUT);
  pinMode(Sr700NothingPin, OUTPUT);
  pinMode(Sr700OkPin, INPUT);
  pinMode(Sr700NgPin, INPUT);
  pinMode(Sr700ErrorPin, INPUT);
  pinMode(Sr700BusyPin, INPUT);

  pinMode(dbIn1Pin, INPUT);
  pinMode(dbIn2Pin, INPUT);
  pinMode(dbIn3Pin, INPUT);
  pinMode(dbIn4Pin, INPUT);

  pinMode(dbOut1Pin, OUTPUT);
  pinMode(dbOut2Pin, OUTPUT);
  pinMode(dbOut3Pin, OUTPUT);
  pinMode(dbOut4Pin, OUTPUT);



  //  pinMode(testPin, OUTPUT);
  //  digitalWrite(testPin, LOW);

  digitalWrite(Sr700ReadPin, LOW);
  digitalWrite(Sr700NothingPin, LOW);

  digitalWrite(dbOut1Pin, LOW);
  digitalWrite(dbOut2Pin, LOW);
  digitalWrite(dbOut3Pin, LOW);
  digitalWrite(dbOut4Pin, LOW);





  Serial.begin(115200);
  Serial1.begin(115200);
  while (!Serial);



}

void loop()
{

SerialIncomingSr700();

SerialIncomingSsif();

//
//  busy_on();
//  delay(200);
//  busy_off();
//  delay(200);
//
//  ok_on();
//  delay(200);
//  ok_off();
//  delay(200);
//
//  ng_on();
//  delay(200);
//  ng_off();
//  delay(200);
//
//  out4_on();
//  delay(200);
//  out4_off();
//  delay(200);

}







/* ---------------------------------------------------
  Method
--------------------------------------------------- */

void checkInPins() {
  
  
  
  
}


/* ---------------------------------------------------
  DieBonder
--------------------------------------------------- */

// digitalWrite

void busy_on() {
  digitalWrite(busyPin, HIGH);
}
void busy_off() {
  digitalWrite(busyPin, LOW);
}

void ok_on() {
  digitalWrite(okPin, HIGH);
}
void ok_off() {
  digitalWrite(okPin, LOW);
}

void ng_on() {
  digitalWrite(ngPin, HIGH);
}
void ng_off() {
  digitalWrite(ngPin, LOW);
}


void out4_on() {
  digitalWrite(dbOut4Pin, HIGH);
}
void out4_off() {
  digitalWrite(dbOut4Pin, LOW);
}




//-----
void Busy(int state) {
  digitalWrite(busyPin, state);
}
void Ok(int state) {
  digitalWrite(busyPin, state);
}
void Ng(int state) {
  digitalWrite(busyPin, state);
}

// digitalRead
int ReadStartPin() {

  return digitalRead(startPin) ;
}





/* ---------------------------------------------------
  SR700
--------------------------------------------------- */



int Sr700ReadCode() {

  static int state = LOW;
  boolean flg = false;


  // SR700 Read Start.
  Serial.println("On1=on");

  digitalWrite(Sr700ReadPin, HIGH);



  int oldBusyState = 0;
  int BusyState = 0;

  delay(10);

  while (1) {
    BusyState = digitalRead(Sr700BusyPin);

    if (oldBusyState == LOW) {
      Serial.println("B=ON");
      break;
    }

    delay(5);
    oldBusyState = BusyState;

    // Wait for BUSY ON.
  }

  delay(100);


  Sr700CodeReadPreviousMillis = millis();
  oldBusyState = 0;
  BusyState = 0;
  while (1) {
    unsigned long cm = millis();

    BusyState = digitalRead(Sr700BusyPin);

    if (BusyState == 1) {
      _brOut1Off();
      //      digitalWrite(testPin, HIGH);
      Serial.println("Busy=OFF");
      break;
    }

    if ((cm - Sr700CodeReadPreviousMillis) >= 1000) {
      // SR700 Read End.
      Serial.print("On1=offffff ");
      Serial.print(cm);
      Serial.print(" ");
      Serial.print(Sr700CodeReadPreviousMillis);
      Serial.print(" ");

      Serial.println(cm - Sr700CodeReadPreviousMillis);



      digitalWrite(Sr700ReadPin, LOW);

    }

    delay(5);
    oldBusyState = BusyState;

  }

  delay(100);

  if (readSr700OkPin() == LOW) {
    Serial.println("Pass Low");

    delay(10);
    _checkSerialIncomingSr700();

    return HIGH;
  }






  if (readSr700NgPin() == LOW) {

    Serial.println("NG LOW");
    delay(10);
    _checkSerialIncomingSr700();


    return LOW;
  }




  //  digitalWrite(testPin, LOW);
}


int readSr700BusyPin() {
  if (digitalRead(Sr700BusyPin) == HIGH) {
    return HIGH;
  }
  else {
    return LOW;
  }
}

int readSr700OkPin() {
  if (digitalRead(Sr700OkPin) == HIGH) {
    return HIGH;
  }
  else {
    return LOW;
  }
}

int readSr700NgPin() {
  if (digitalRead(Sr700NgPin) == HIGH) {
    return HIGH;
  }
  else {
    return LOW;
  }
}



void _brOut1On() {
  digitalWrite(Sr700ReadPin, HIGH);
}
void _brOut1Off() {
  digitalWrite(Sr700ReadPin, LOW);
}
void _brOut2On() {
  digitalWrite(Sr700NothingPin, HIGH);
}
void _brOut2Off() {
  digitalWrite(Sr700NothingPin, LOW);
}





/* ---------------------------------------------------
  SERIALs
--------------------------------------------------- */

// -- Serial Event --
void SerialIncomingSsif() {
  Serial.print(strSerialIncomingSsif);
}

void SerialIncomingSr700() {
  Serial.print(strSerialIncomingSr700);
}


void checkSerials() {
  _checkSerialIncomingSsif();
  _checkSerialIncomingSr700();
}

void _checkSerialIncomingSsif() {
  __serialReadLineSsifCheckSsif();
  strSerialIncomingSsif = serialReadLineSsif();
      SerialIncomingSsif();

  if (strSerialIncomingSsif.length() > 0) {
  }
}
void _checkSerialIncomingSr700() {
  __serialReadLineSsifCheckSsifSr700();
  strSerialIncomingSr700 = __serialReadLineSsifSr700();
      SerialIncomingSr700();

  if (strSerialIncomingSr700.length() > 0) {
  }

}



//-Serial SSIF --------------------------------------
String _strSerialIncomingSsif, _strBuf;
int _readFlg = 0;

void __serialReadLineSsifCheckSsif(void) {
  while (Serial.available()) {
    //delay(3);  //delay to allow buffer
    if (Serial.available() > 0) {
      char c = Serial.read();  //gets one byte from serial buffer
      if ((_readFlg == 0) && ((c == '\r') || (c == '\n'))) {
        _strSerialIncomingSsif = _strBuf;
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

String serialReadLineSsif(void) {
  String s = "";
  if (_readFlg) {
    s = _strSerialIncomingSsif; //see what was received
    _strSerialIncomingSsif = "";
    _readFlg = 0;
  }
  return s;
}

//-Serial SR700 --------------------------------------
String _strSerialIncomingSr700, _strBuf1;
int _readFlg1 = 0;

void __serialReadLineSsifCheckSsifSr700(void) {
  while (Serial1.available()) {
    //delay(3);  //delay to allow buffer
    if (Serial1.available() > 0) {
      char c = Serial1.read();  //gets one byte from serial buffer
      if ((_readFlg1 == 0) && ((c == '\r') || (c == '\n'))) {
        _strSerialIncomingSr700 = _strBuf1;
        _strBuf1 = "";
        _readFlg1 = 1;
      }
      else if ((_readFlg1 == 1) && ((c == '\r') || (c == '\n'))) {
        //do nothing
      }
      else {
        _strBuf1 += c;
      }
    }
  }
}

String __serialReadLineSsifSr700(void) {
  String s = "";
  if (_readFlg1) {
    s = _strSerialIncomingSr700; //see what was received
    _strSerialIncomingSr700 = "";
    _readFlg1 = 0;
  }
  return s;
}

// --- END OF CODE ---
