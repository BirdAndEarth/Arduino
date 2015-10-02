
String strSeriaIncomingSsif = "";         // a string to hold incoming data
String strSeriaIncomingSr700 = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
boolean stringComplete1 = false;  // whether the string is complete



void setup() {

  // initialize serial:
  Serial.begin(115200);
  Serial1.begin(115200);
  // reserve 200 bytes for the strSeriaIncomingSsif:
  strSeriaIncomingSsif.reserve(200);
  strSeriaIncomingSr700.reserve(200);

  while(Serial);


}

void loop() {
  serialCheck();
  serial1Check();

  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.print(strSeriaIncomingSsif);
    // clear the string:
    strSeriaIncomingSsif = "";
    stringComplete = false;
  }
  // print the string when a newline arrives:
  if (stringComplete1) {
    Serial.print(strSeriaIncomingSr700);
    // clear the string:
    strSeriaIncomingSr700 = "";
    stringComplete1 = false;
  }







}


void serialCheck() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    strSeriaIncomingSsif += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void serial1Check() {
  while (Serial1.available()) {
    char inChar = (char)Serial1.read();
    strSeriaIncomingSr700 += inChar;
    if (inChar == '\n') {
      stringComplete1 = true;
    }
  }
}

