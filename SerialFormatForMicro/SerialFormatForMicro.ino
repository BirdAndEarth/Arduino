#include "dv32u.h"

/*******************************************************************
 SERIALs
 *******************************************************************/
/* Serials */
String strSeriaIncoming = "";         // a string to hold incoming data
String strSeriaIncoming1 = "";         // a string to hold incoming data

boolean blnStringComplete = false;  // whether the string is complete
boolean blnStringComplete1 = false;  // whether the string is complete

void serialInit() {
  // initialize serial:
  Serial.begin(115200);
  Serial1.begin(115200);

  // reserve 200 bytes for the strSeriaIncoming1:
  strSeriaIncoming.reserve(200);
  strSeriaIncoming1.reserve(200);
}

void serialCheck() {
  serialIncomingCheck();
  serialIncomingCheck1();
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

void serialComplete() {
  // Serial
  if (blnStringComplete) {
    serialCommandRecieve(strSeriaIncoming);
    strSeriaIncoming = "";
    blnStringComplete = false;
  }
  // Serial1
  if (blnStringComplete1) {
    serialCommandRecieve1(strSeriaIncoming1);
    strSeriaIncoming1 = "";
    blnStringComplete1 = false;
  }
}

void serialCommandRecieve(String command) {
  dbg("Serial<\t" + command);

}
void serialCommandRecieve1(String command) {
  dbg("Serial1<\t" + command);

}

void dbg(String text) {
  Serial.print(millis());
  Serial.print('\t');
  Serial.print(text);
}
void dbgln(String text) {
  Serial.print(millis());
  Serial.print('\t');
  Serial.println(text);
}
/* SERIALs END ******************************************************/










/* =======================================================================================
 setup
=========================================================================================== */
void setup() {
  serialInit();
}


/* =======================================================================================
 loop
=========================================================================================== */
void loop() {
  serialCheck();

}

// -- END OF CODE ----------------------------------------------------------

