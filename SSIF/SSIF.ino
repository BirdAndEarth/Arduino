/*************************************************
 * SSIF for DB
 *  15/09/28  Rev.1.0  New.
 *  15/09/29  Rev.1.1  add SERIAL_LINE_DELAY
 *************************************************/
#include "dv32u.h"

String PVER = "1.1";
String PNAME = "SSIF";

boolean DBG = false; // Debug Mode

const int SERIAL_LINE_DELAY = 20; // send line delay ms.


/* Serial */
String strSerialIncomingSsif = "";         // a string to hold incoming data
String strSerialIncomingSr700 = "";        // a string to hold incoming data
boolean blnStringCompleteSsif = false;     // whether the string is complete
boolean blnStringCompleteSr700 = false;    // whether the string is complete


/* Pins */
//  name              DaVinci Pin Name
int Sr700ReadPin    = PD6;
int Sr700NothingPin = PD7;
int Sr700OkPin      = PF7;
int Sr700NgPin      = PF6;
int Sr700ErrorPin   = PF5;
int Sr700BusyPin    = PF4;

int dbIn1Pin = PB0; // DB IN1
int dbIn2Pin = PB1; // DB IN2
int dbIn3Pin = PB2; // DB IN3
int dbIn4Pin = PB3; // DB IN4

int dbOut1Pin = PB4; // DB OUT1
int dbOut2Pin = PB5; // DB OUT2
int dbOut3Pin = PB6; // DB OUT3
int dbOut4Pin = PB7; // DB OUT4

int ledPin = PC7; // LED

// alias
int startPin    = dbIn1Pin;
int lotClearPin = dbIn2Pin;
int busyPin     = dbOut1Pin;
int okPin       = dbOut2Pin;
int ngPin       = dbOut3Pin;

// variables
String frameId = "";

// consts
unsigned long ResultTimeOutMs = 20000;

/*************************************
 setup()
 *************************************/
void setup() {

  initializePins();
  initializeSerials();

  /* initialize */
  // Not ready because SSIF Serial Port does not Open
  busy_on();

  // loop() is not start till SSIF Serial Port Open
  while (!Serial);

  _debug("-----------");
  _debug("SSIF Start!");
  _debug("-----------");
  _debug("(Wait until SSIF is ready [R:]....)"); //debug
}

/*************************************
 loop()
 *************************************/

void loop() {
  static boolean ssifReadyFlg = false;
  int iResult = 0; //

  /* Wait for SSif is ready */
  if (serialCheckSsif()) {
    String ssifIncoming = readSsif();
    _debug("SerialSsif Recieve:[" + ssifIncoming + "]");

    // SSIF READY
    if (ssifIncoming == "R:") {
      _debug("(SSIF is READY.)");
      ssifReadyFlg = true;
      clearSr700();
      resetPins();
      busy_off();
    }

    // SSIF NOT READY
    else if (ssifIncoming == "r:") {
      _debug("(SSIF is NOT READY.)");
      ssifReadyFlg = false;
      clearOkNg();
      clearSr700();
      busy_on();
    }

    /* for debug */
    if (!ssifReadyFlg) {
      // - Output Signal Debug
      if (ssifIncoming == "O1:") {
        busy_on();
        goto LAST;
      }
      else if (ssifIncoming == "O2:") {
        ok_on();
        goto LAST;
      }
      else if (ssifIncoming == "O3:") {
        ng_on();
        goto LAST;
      }
      else if (ssifIncoming == "O4:") {
        out4_on();
        goto LAST;
      }
      else if (ssifIncoming == "o1:") {
        busy_off();
        goto LAST;
      }
      else if (ssifIncoming == "o2:") {
        ok_off;
        goto LAST;
      }
      else if (ssifIncoming == "o3:") {
        ng_off();
        goto LAST;
      }
      else if (ssifIncoming == "o4:") {
        out4_off;
        goto LAST;
      }

      // - Input Signal Debug
      else if (ssifIncoming == "i:") {
        String str = "i:";
        str += String(!digitalRead(dbIn1Pin));
        str += String(!digitalRead(dbIn2Pin));
        str += String(!digitalRead(dbIn3Pin));
        str += String(!digitalRead(dbIn4Pin));
        sendSsif(str);
        goto LAST;
      }

      // - debug mode sw
      else if (ssifIncoming == "D:") {
        DBG = true;
        _debug("(Debug Mode = ON)");
        goto LAST;
      }
      else if (ssifIncoming == "d:") {
        DBG = false;
        goto LAST;
      }

    }
  }

  /* If SSIF is not ready, jump to LAST:.*/
  if (!ssifReadyFlg) {
    goto LAST;
  }

  /* Check to Fid incoming. */
  if (serialCheckSr700()) {
    String sr700Incoming = readSr700();
    _debug("Serialsr700 Recieve:[" + sr700Incoming + "]");
    frameId = sr700Incoming;
    _debug("FrameId = " + frameId); // for debug
  }

  /* Check the LotClear Signal. */
  if (readLotClearPin() && ssifReadyFlg) {
    _debug("Recieve Lot Clear Signal.");
    _debug("send [L:] to SSIF.");
    clearOkNg();
    ssifReadyFlg = false;
    frameId = "";
    busy_on();
    sendSsif("L:"); // send Lot Clear to SSIF
    goto LAST;
  }

  /* check for the Start Signal. */
  if (!readStartPin()) {
    goto LAST;
  }

  /* when the Start signal on. */
  _debug("Start Signal ON:");

  // Start normaly
  if (frameId != "") {
    clearOkNg();
    busy_on();
    sendSsif("Q:" + frameId); //send FrameId judge request.
  }
  // Start befor Read (send ERROR to ssif).
  else {
    clearOkNg();
    busy_on();
    sendSsif("E:Start before read."); // send error to SSIF.
    ng_on();
    delay(10);
    clearSr700();
    busy_off();
    _debug("Result = NG");
    goto LAST;
  }

  /* Wait for the judge result. */
  switch (waitForResult()) {

    case 0: // FrameId OK.
      ok_on();
      delay(10);
      clearSr700();
      busy_off();
      _debug("Result = OK");
      break;

    case 1: // FrameId NG.
      ng_on();
      delay(10);
      clearSr700();
      busy_off();
      _debug("Result = NG");
      break;

    default: // Request Timed out.
      clearOkNg();
      delay(10);
      busy_off();
      clearSr700();
      ssifReadyFlg = false;
      _debug("Result = Timeout");
      _debug("SSIF is NOT READY");
      goto LAST;
  }


  /* Loop End */
LAST:
  //  if (1); // do nothing.
  led(ssifReadyFlg); // When SS is ready, LED is ON
}


/* ---------------------------------------------------
 MISC
--------------------------------------------------- */

void clearOkNg() {
  ok_off();
  ng_off();
}

void resetPins() {
  busy_off();
  ok_off();
  ng_off();
  out4_off();
}

// Clear SR700 Incoming text and reset flg.
void clearSr700() {
  serialCheckSr700();
  readSr700();
  frameId = "";
  strSerialIncomingSr700 = "";
  blnStringCompleteSr700 = false;
}

int waitForResult() {
  unsigned long timerStart = millis(); // update current time.
  unsigned long timerBlink = millis(); // update current time.
  unsigned long blinkIntervalMs = 100; // LED Blink interval

  boolean st = false;
  _debug("waitForResult: ");

  while (1) {
    // LED Blink
    if (millis() - timerBlink > blinkIntervalMs) {
      timerBlink = millis();
      st = !st;
      led(st);
    }

    // Check for the time out.
    if (millis() - timerStart > ResultTimeOutMs) {
      return 2;
    }

    // Wait for the Answer.
    if (serialCheckSsif()) {
      String result = readSsif();
      _debug("SerialSsif Recieve:[" + result + "]");
      if (result == "A:OK") {
        return 0;
      }
      else if (result == "A:NG") {
        return 1;
      }
    }
  }
}

void led(boolean state) {
  if (state) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}


/* ---------------------------------------------------
 Initialize
--------------------------------------------------- */

void initializePins() {

  /* initialize Pins */
  pinMode(Sr700ReadPin, OUTPUT);
  pinMode(Sr700NothingPin, OUTPUT);
  pinMode(Sr700OkPin, INPUT);
  pinMode(Sr700NgPin, INPUT);
  pinMode(Sr700ErrorPin, INPUT);
  pinMode(Sr700BusyPin, INPUT);

  pinMode(dbIn1Pin, INPUT_PULLUP);
  pinMode(dbIn2Pin, INPUT_PULLUP);
  pinMode(dbIn3Pin, INPUT_PULLUP);
  pinMode(dbIn4Pin, INPUT_PULLUP);

  pinMode(dbOut1Pin, OUTPUT);
  pinMode(dbOut2Pin, OUTPUT);
  pinMode(dbOut3Pin, OUTPUT);
  pinMode(dbOut4Pin, OUTPUT);

  pinMode(ledPin, OUTPUT);

  digitalWrite(Sr700ReadPin, LOW);
  digitalWrite(Sr700NothingPin, LOW);

  digitalWrite(dbOut1Pin, LOW);
  digitalWrite(dbOut2Pin, LOW);
  digitalWrite(dbOut3Pin, LOW);
  digitalWrite(dbOut4Pin, LOW);

  digitalWrite(ledPin, LOW);
}

void initializeSerials() {
  /* initialize Serials */
  Serial.begin(115200);  // SSIF
  Serial1.begin(115200); // SR-700

  // reserve 200 bytes for the incoming strings:
  strSerialIncomingSsif.reserve(200);
  strSerialIncomingSr700.reserve(200);
  frameId.reserve(200);

}

/* ---------------------------------------------------
  SS I/F
--------------------------------------------------- */

void sendInputState() {
  Serial.print("i:");
  Serial.print(readStartPin());
  Serial.print(readLotClearPin());
  Serial.print(readDbIn3Pin());
  Serial.print(readDbIn4Pin());
  Serial.println("");
}


/* ---------------------------------------------------
  DieBonder
--------------------------------------------------- */

/* digitalWrite */

// busy (OUT 1)
void busy_on() {
  digitalWrite(busyPin, HIGH);
  _debug(" busy_on");
  delay(100);
}
void busy_off() {
  digitalWrite(busyPin, LOW);
  _debug(" busy_off");
}

// ok (OUT 2)
void ok_on() {
  digitalWrite(okPin, HIGH);
  _debug(" ok_on");
}
void ok_off() {
  digitalWrite(okPin, LOW);
  _debug(" ok_off");
}

// ng (OUT 3)
void ng_on() {
  digitalWrite(ngPin, HIGH);
  _debug(" ng_on");
}
void ng_off() {
  digitalWrite(ngPin, LOW);
  _debug(" ng_off");
}

// reserved (OUT 4)
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

/* digitalRead */
// Input pins from DB are Active Low.
// So, invert the read states.

// Start (IN 1)
boolean readStartPin() {
  if (digitalRead(startPin)) {
    return false;
  } else {
    return true;
  }
}
// Lot Clear (IN 2)
boolean readLotClearPin() {
  if (digitalRead(lotClearPin)) {
    return false;
  } else {
    return true;
  }
}
// (IN 3)
boolean readDbIn3Pin() {
  if (digitalRead(dbIn3Pin)) {
    return false;
  } else {
    return true;
  }
}
// (IN 4)
boolean readDbIn4Pin() {
  if (digitalRead(dbIn4Pin)) {
    return false;
  } else {
    return true;
  }
}


/* ---------------------------------------------------
  Serials
--------------------------------------------------- */
void serialCheck() {
  serialCheckSsif();
  serialCheckSr700();
}

boolean serialCheckSsif() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();

    // Ignore terminate character
    if (inChar != '\r' && inChar != '\n') {
      strSerialIncomingSsif += inChar;
    }

    // Detect terminate character
    if (inChar == '\n') {
      blnStringCompleteSsif = true;
      return true;
    }
  }
  return false;
}


String readSsif() {
  String strReturn = "";
  if (blnStringCompleteSsif) {
    strReturn = strSerialIncomingSsif;
    // clear the string:
    strSerialIncomingSsif = "";
    blnStringCompleteSsif = false;
  }
  return strReturn;
}

boolean serialCheckSr700() {
  while (Serial1.available()) {
    char inChar = (char)Serial1.read();

    // Ignore terminate character
    if (inChar != '\r' && inChar != '\n') {
      strSerialIncomingSr700 += inChar;
    }

    // Detect terminate character
    if (inChar == '\n') {
      blnStringCompleteSr700 = true;
      return true;
    }
  }
  return false;
}

String readSr700() {
  String strReturn = "";
  if (blnStringCompleteSr700) {
    strReturn = strSerialIncomingSr700;
    // clear the string:
    strSerialIncomingSr700 = "";
    blnStringCompleteSr700 = false;
  }
  return strReturn;
}


void sendSsif(String sendString1) {
  Serial.println(sendString1);
  delay(SERIAL_LINE_DELAY);
}


/* ---------------------------------------------------
  Debug
--------------------------------------------------- */
void _debug(String str) {
  if (DBG) {
    Serial.println("debug:" + str);
    delay(SERIAL_LINE_DELAY);
  }
}

// ----- END OF CODE -----
