#include "dv32u.h"


/*******************************************************************
 SERIALs
 *******************************************************************/

void serialInit() {
  // initialize serial:
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);

  // reserve 200 bytes for the strSeriaIncoming1:
  strSeriaIncoming.reserve(200);
  strSeriaIncoming1.reserve(200);
  strSeriaIncoming2.reserve(200);
  strSeriaIncoming3.reserve(200);

}

void serialCheck() {
  serialIncomingCheck();
  serialIncomingCheck1();
  serialIncomingCheck2();
  serialIncomingCheck3();
  serialComplete();
}


void serialIncomingCheck() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    strSeriaIncoming += inChar;
    if (inChar == '\n') {
      blnStringComplete = true;
    }
  }
}

void serialIncomingCheck1() {
  while (Serial1.available()) {
    char inChar = (char)Serial1.read();
    strSeriaIncoming1 += inChar;
    if (inChar == '\n') {
      blnStringComplete1 = true;
    }
  }
}

void serialIncomingCheck2() {
  while (Serial2.available()) {
    char inChar = (char)Serial2.read();
    strSeriaIncoming2 += inChar;
    if (inChar == '\n') {
      blnStringComplete2 = true;
    }
  }
}

void serialIncomingCheck3() {
  while (Serial3.available()) {
    char inChar = (char)Serial3.read();
    strSeriaIncoming3 += inChar;
    if (inChar == '\n') {
      blnStringComplete3 = true;
    }
  }
}

void serialComplete() {
  // Serial USB
  if (blnStringComplete) {
    serialCommandRecieve(strSeriaIncoming);
    strSeriaIncoming = "";
    blnStringComplete = false;
  }
  // Serial 1
  if (blnStringComplete1) {
    serialCommandRecieve1(strSeriaIncoming1);
    strSeriaIncoming1 = "";
    blnStringComplete1 = false;
  }
  // Serial2
  if (blnStringComplete2) {
    serialCommandRecieve2(strSeriaIncoming2);
    strSeriaIncoming2 = "";
    blnStringComplete2 = false;
  }
  // Serial3
  if (blnStringComplete3) {
    serialCommandRecieve3(strSeriaIncoming3);
    strSeriaIncoming3 = "";
    blnStringComplete3 = false;
  }
}

void serialCommandRecieve(String command) {
  dbg("Rx<\t" + command);

}
void serialCommandRecieve1(String command) {
  dbg("Rx1<\t" + command);

}
void serialCommandRecieve2(String command) {
  dbg("Rx2<\t" + command);

}
void serialCommandRecieve3(String command) {
  dbg("Rx3<\t" + command);

}


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
