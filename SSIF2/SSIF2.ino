/*************************************
 * SSIF for DB
 *  15/09/11  Rev.0.0  shiu  New.
 *************************************/

String strSeriaIncomingSsif = "";         // a string to hold incoming data
String strSeriaIncomingSr700 = "";         // a string to hold incoming data
boolean blnStringCompleteSsif= false;  // whether the string is complete
boolean blnStringCompleteSr700 = false;  // whether the string is complete

void setup() {

  // initialize serial:
  Serial.begin(115200);  // SSIF
  Serial1.begin(115200); // SR-700

  // reserve 200 bytes for the strSeriaIncomingSsif:
  strSeriaIncomingSsif.reserve(200);
  strSeriaIncomingSr700.reserve(200);

  while(!Serial); // wait for SSIF Serial Port Open

}

void loop() {
  serialCheckSsif();
  serialCheckSr700();

  // print the string when a newline arrives:
  if (blnStringCompleteSsif) {
    Serial.print(strSeriaIncomingSsif);
    // clear the string:
    strSeriaIncomingSsif = "";
    blnStringCompleteSsif= false;
  }
  // print the string when a newline arrives:
  if (blnStringCompleteSr700) {
    Serial.print(strSeriaIncomingSr700);
    // clear the string:
    strSeriaIncomingSr700 = "";
    blnStringCompleteSr700 = false;
  }







}


void serialCheckSsif() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    strSeriaIncomingSsif += inChar;
    if (inChar == '\n') {
      blnStringCompleteSsif= true;
    }
  }
}

void serialCheckSr700() {
  while (Serial1.available()) {
    char inChar = (char)Serial1.read();
    strSeriaIncomingSr700 += inChar;
    if (inChar == '\n') {
      blnStringCompleteSr700 = true;
    }
  }
}

