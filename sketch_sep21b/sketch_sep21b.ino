

String strSeriaIncomingSsif = "";         // a string to hold incoming data
boolean blnStringCompleteSsif = false; // whether the string is complete

void setup() {
  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  if (serialCheckSsif()) {
    Serial.print(ReadSsif());
  }
}

// ------------------------------------

boolean serialCheckSsif() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    strSeriaIncomingSsif += inChar;
    if (inChar == '\n') {
      blnStringCompleteSsif = true;
      return true;
    }
  }
  return false;
}

String ReadSsif() {
  String strReturn = "";
  if (blnStringCompleteSsif) {
    strReturn = strSeriaIncomingSsif;
    // clear the string:
    strSeriaIncomingSsif = "";
    blnStringCompleteSsif = false;
  }
  return strReturn;
}

