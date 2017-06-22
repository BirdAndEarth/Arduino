/*
  _|_|_|  _|_|_|_|  _|_|_|    _|_|_|    _|_|    _|
_|        _|        _|    _|    _|    _|    _|  _|          _|_|_|
  _|_|    _|_|_|    _|_|_|      _|    _|_|_|_|  _|        _|_|
      _|  _|        _|    _|    _|    _|    _|  _|            _|_|
_|_|_|    _|_|_|_|  _|    _|  _|_|_|  _|    _|  _|_|_|_|  _|_|_|
*/
String  strSeriaIncoming;
String  strSeriaIncoming1;
String  strSeriaIncoming2;
String  strSeriaIncoming3;

boolean blnStringComplete;
boolean blnStringComplete1;
boolean blnStringComplete2;
boolean blnStringComplete3;

void serialInit() {
  // initialize serial:
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);

  // reserve 200 bytes for the strSeriaIncomings
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
  serialComplete1();
  serialComplete2();
  serialComplete3();
}


void serialIncomingCheck() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      blnStringComplete = true;
    }
    else if (inChar == '\r') {
      // Ignore CR (do nothing)
    }
    else {
      strSeriaIncoming += inChar;
    }
  }
}

void serialIncomingCheck1() {
  while (Serial1.available()) {
    char inChar = (char)Serial1.read();
    if (inChar == '\n') {
      blnStringComplete1 = true;
    }
    else if (inChar == '\r') {
      // Ignore CR (do nothing)
    }
    else {
      strSeriaIncoming1 += inChar;
    }
  }
}

void serialIncomingCheck2() {
  while (Serial2.available()) {
    char inChar = (char)Serial2.read();
    if (inChar == '\n') {
      blnStringComplete2 = true;
    }
    else if (inChar == '\r') {
      // Ignore CR (do nothing)
    }
    else {
      strSeriaIncoming2 += inChar;
    }
  }
}

void serialIncomingCheck3() {
  while (Serial3.available()) {
    char inChar = (char)Serial3.read();
    if (inChar == '\n') {
      blnStringComplete3 = true;
    }
    else if (inChar == '\r') {
      // Ignore CR (do nothing)
    }
    else {
      strSeriaIncoming3 += inChar;
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
}

void serialComplete1() {
  // Serial 1
  if (blnStringComplete1) {
    serialCommandRecieve1(strSeriaIncoming1);
    strSeriaIncoming1 = "";
    blnStringComplete1 = false;
  }
}
void serialComplete2() {
  // Serial2
  if (blnStringComplete2) {
    serialCommandRecieve2(strSeriaIncoming2);
    strSeriaIncoming2 = "";
    blnStringComplete2 = false;
  }
}
void serialComplete3() {
  // Serial3
  if (blnStringComplete3) {
    serialCommandRecieve3(strSeriaIncoming3);
    strSeriaIncoming3 = "";
    blnStringComplete3 = false;
  }
}

void serialCommandRecieve(String command) {


}
void serialCommandRecieve1(String command) {


}
void serialCommandRecieve2(String command) {


}
void serialCommandRecieve3(String command) {


}


/*
_|      _|  _|_|_|_|  _|_|_|_|_|  _|    _|    _|_|    _|_|_|
_|_|  _|_|  _|            _|      _|    _|  _|    _|  _|    _|    _|_|_|
_|  _|  _|  _|_|_|        _|      _|_|_|_|  _|    _|  _|    _|  _|_|
_|      _|  _|            _|      _|    _|  _|    _|  _|    _|      _|_|
_|      _|  _|_|_|_|      _|      _|    _|    _|_|    _|_|_|    _|_|_|
*/










/*
  _|_|_|  _|_|_|_|  _|_|_|_|_|  _|    _|  _|_|_|
_|        _|            _|      _|    _|  _|    _|
  _|_|    _|_|_|        _|      _|    _|  _|_|_|
      _|  _|            _|      _|    _|  _|
_|_|_|    _|_|_|_|      _|        _|_|    _|
*/
void setup() {
  // put your setup code here, to run once:

}


/*
_|          _|_|      _|_|    _|_|_|
_|        _|    _|  _|    _|  _|    _|
_|        _|    _|  _|    _|  _|_|_|
_|        _|    _|  _|    _|  _|
_|_|_|_|    _|_|      _|_|    _|
*/
void loop() {
  // put your main code here, to run repeatedly:

}
