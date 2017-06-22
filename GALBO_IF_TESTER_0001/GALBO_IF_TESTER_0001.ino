/*******************************************************************************
  Galvo IF TESTER
  17/03/16  0001  SY

*******************************************************************************/
#include <SPI.h>

SPIClass SPI_2(2);
int latchPin = 31;


/*
  _|_|_|  _|_|_|_|  _|_|_|    _|_|_|    _|_|    _|
_|        _|        _|    _|    _|    _|    _|  _|          _|_|_|
  _|_|    _|_|_|    _|_|_|      _|    _|_|_|_|  _|        _|_|
      _|  _|        _|    _|    _|    _|    _|  _|            _|_|
_|_|_|    _|_|_|_|  _|    _|  _|_|_|  _|    _|  _|_|_|_|  _|_|_|
*/

String  serialIncoming;
String  serialIncoming1;
String  serialIncoming2;
String  serialIncoming3;

boolean stringComplete;
boolean stringComplete1;
boolean stringComplete2;
boolean stringComplete3;

void serialInit() {
  // initialize serial:
  //  Serial.begin(115200);
  Serial1.begin(115200);
  //  Serial2.begin(115200);
  //  Serial3.begin(115200);

  // reserve 200 bytes for the serialIncomings
  serialIncoming.reserve(255);
  serialIncoming1.reserve(255);
  serialIncoming2.reserve(255);
  serialIncoming3.reserve(255);
}

void serialCheck() {
  //  serialIncomingCheck();
  serialIncomingCheck1();
  //  serialIncomingCheck2();
  //  serialIncomingCheck3();
  //  serialComplete();
  serialComplete1();
  //  serialComplete2();
  //  serialComplete3();
}


void serialIncomingCheck() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    }
    else if (inChar == '\r') {
      // Ignore CR (do nothing)
    }
    else {
      serialIncoming += inChar;
    }
  }
}

void serialIncomingCheck1() {
  while (Serial1.available()) {
    char inChar = (char)Serial1.read();
    if (inChar == '\n') {
      stringComplete1 = true;
    }
    else if (inChar == '\r') {
      // Ignore CR (do nothing)
    }
    else {
      serialIncoming1 += inChar;
    }
  }
}

void serialIncomingCheck2() {
  while (Serial2.available()) {
    char inChar = (char)Serial2.read();
    if (inChar == '\n') {
      stringComplete2 = true;
    }
    else if (inChar == '\r') {
      // Ignore CR (do nothing)
    }
    else {
      serialIncoming2 += inChar;
    }
  }
}

void serialIncomingCheck3() {
  while (Serial3.available()) {
    char inChar = (char)Serial3.read();
    if (inChar == '\n') {
      stringComplete3 = true;
    }
    else if (inChar == '\r') {
      // Ignore CR (do nothing)
    }
    else {
      serialIncoming3 += inChar;
    }
  }
}

void serialComplete() {
  // Serial USB
  if (stringComplete) {
    serialCommandRecieve(serialIncoming);
    serialIncoming = "";
    stringComplete = false;
  }
}

void serialComplete1() {
  // Serial 1
  if (stringComplete1) {
    serialCommandRecieve1(serialIncoming1);
    serialIncoming1 = "";
    stringComplete1 = false;
  }
}
void serialComplete2() {
  // Serial2
  if (stringComplete2) {
    serialCommandRecieve2(serialIncoming2);
    serialIncoming2 = "";
    stringComplete2 = false;
  }
}
void serialComplete3() {
  // Serial3
  if (stringComplete3) {
    serialCommandRecieve3(serialIncoming3);
    serialIncoming3 = "";
    stringComplete3 = false;
  }
}

/* Recieves */
void serialCommandRecieve(String command) {

}
void serialCommandRecieve1(String command) {
  commandRecieve(command);
}
void serialCommandRecieve2(String command) {
}
void serialCommandRecieve3(String command) {
}

/* Sends */
void serialSend(String text) {
  Serial.print(text);
}
void serialSend1(String text) {
  Serial1.print(text);
}
void serialSend2(String text) {
  Serial2.print(text);
}
void serialSend3(String text) {
  Serial3.print(text);
}

/*
_|      _|  _|_|_|_|  _|_|_|_|_|  _|    _|    _|_|    _|_|_|
_|_|  _|_|  _|            _|      _|    _|  _|    _|  _|    _|    _|_|_|
_|  _|  _|  _|_|_|        _|      _|_|_|_|  _|    _|  _|    _|  _|_|
_|      _|  _|            _|      _|    _|  _|    _|  _|    _|      _|_|
_|      _|  _|_|_|_|      _|      _|    _|    _|_|    _|_|_|    _|_|_|
METHODs */

void commandRecieve(String command) {
  paraSend(hex2dec(command));
}

/* MISCs */
int hex2dec(String s) {
  int d = 0;
  for (int i = s.length() - 1; i >= 0; i--) {
    d += _hex2dec(s.charAt(s.length() - 1 - i)) << (4 * i);
  }
  serialSend1(s + '\t');
  serialSend1(String(d) + "\r\n");
  return d;
}

int _hex2dec(char c) {
  switch (c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'A': return 10;
    case 'B': return 11;
    case 'C': return 12;
    case 'D': return 13;
    case 'E': return 14;
    case 'F': return 15;
    case 'a': return 10;
    case 'b': return 11;
    case 'c': return 12;
    case 'd': return 13;
    case 'e': return 14;
    case 'f': return 15;
    default:
      return 0;
  }
}


/* PALLARELs */
void paraSend(int data) {
  unsigned long data32 = data;
  byte data1;
  byte data2;
  byte data3;

  data1 = data32 >> 16;
  data2 = data32 >> 8;
  data3 = data32;

  digitalWrite(latchPin, 0);

  SPI_2.transfer(data1);
  SPI_2.transfer(data2);
  SPI_2.transfer(data3);

  digitalWrite(latchPin, 1);
}

/* init */
void inits() {
  serialInit();
  pinMode(latchPin, OUTPUT);
  SPI_2.begin();
  SPI_2.setBitOrder(MSBFIRST);
  SPI_2.setClockDivider(SPI_CLOCK_DIV16);
  SPI_2.setDataMode(SPI_MODE0);
  digitalWrite(latchPin, LOW);
}

/*
  _|_|_|  _|_|_|_|  _|_|_|_|_|  _|    _|  _|_|_|
_|        _|            _|      _|    _|  _|    _|
  _|_|    _|_|_|        _|      _|    _|  _|_|_|
      _|  _|            _|      _|    _|  _|
_|_|_|    _|_|_|_|      _|        _|_|    _|
SETUP */

void setup() {
  inits();
  delay(2000);
  //  serialSend("Serial Ready\r\n");
  serialSend1("\r\n");
  serialSend1("GALVO IF TESTER READY \r\n");
  serialSend1("\r\n");
  //  serialSend2("Serial2 Ready\r\n");
  //  serialSend3("Serial3 Ready\r\n");





}


/*
_|          _|_|      _|_|    _|_|_|
_|        _|    _|  _|    _|  _|    _|
_|        _|    _|  _|    _|  _|_|_|
_|        _|    _|  _|    _|  _|
_|_|_|_|    _|_|      _|_|    _|
LOOP */

void loop() {
  serialCheck();
}


