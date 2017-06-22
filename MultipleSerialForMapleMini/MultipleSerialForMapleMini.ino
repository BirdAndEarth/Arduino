//=================================================
// Multiple Serial For Maple Mini
//                 Rev. 1 16/01/21 shiu
//
//=================================================



#define PASS     1
#define FAIL    -1
#define TIMEOUT -2

#define SERIAL_BUFFER_SIZE   1024
#define SERIAL_TIMEOUT_MS    1000
#define COM_BAUD_RATE      115200
#define COM1_BAUD_RATE       9600
#define COM2_BAUD_RATE       9600
#define COM3_BAUD_RATE       9600




void setup() {
  // put your setup code here, to run once:
  Serial.begin(COM_BAUD_RATE);
  Serial1.begin(COM1_BAUD_RATE);
  Serial2.begin(COM2_BAUD_RATE);
  Serial3.begin(COM3_BAUD_RATE);

  com_sendln("com ready");
  com1_sendln("com1 ready");
  com2_sendln("com2 ready");
  com3_sendln("com3 ready");



}

void loop() {
  char com_incomingLine[SERIAL_BUFFER_SIZE];
  char com1_incomingLine[SERIAL_BUFFER_SIZE];
  char com2_incomingLine[SERIAL_BUFFER_SIZE];
  char com3_incomingLine[SERIAL_BUFFER_SIZE];

  // Serial1
  switch (com1_check(com1_incomingLine)) {
    case PASS:
      com2_sendln(com1_incomingLine);

      com_send("[1]");
      com_sendln(com1_incomingLine);
      break;
    case FAIL:
      break;
    case TIMEOUT:
      com_send("[1]");
      com_send(com1_incomingLine);
      com_sendln("<TO>");
      
      break;
  }


  // Serial2
  switch (com2_check(com2_incomingLine)) {
    case PASS:
      com1_sendln(com2_incomingLine);

      com_send("[2]");
      com_sendln(com2_incomingLine);
      break;
    case FAIL:
      break;
    case TIMEOUT:
      com_send("[2]");
      com_send(com2_incomingLine);
      com_sendln("<TO>");
      break;
  }
















}



// ===============================================================
// SERIALs
// ===============================================================

// Serial  -------------------------------------------------------
int com_check(char *incomingLine) {
  static char line[SERIAL_BUFFER_SIZE];
  static int letterNo = 0;
  static unsigned long timerStart = 0;
  static boolean isNotComplete = false;

  // Serial Read
  while (Serial.available()) {
    int incoming = Serial.read();
    if (incoming != '\r' && incoming != '\n') {
      line[letterNo] = incoming;
      letterNo++;
      isNotComplete = true;
      timerStart = millis();
    }
    else if (letterNo != 0) {
      line[letterNo] = '\0';
      sprintf(incomingLine, line);
      letterNo = 0;
      isNotComplete = false;
      return PASS;
    }
  }

  // timeout check
  if (isNotComplete && isTimeout(timerStart, SERIAL_TIMEOUT_MS)) {
    line[letterNo] = '\0';
    sprintf(incomingLine, line);
    letterNo = 0;
    isNotComplete = false;
    return TIMEOUT;
  }

  return FAIL;
}


void com_send(char *c) {
  Serial.print(c);
}
void com_sendln(char *c) {
  Serial.println(c);
}


// Serial1 -------------------------------------------------------
int com1_check(char *incomingLine) {
  static char line[SERIAL_BUFFER_SIZE];
  static int letterNo = 0;
  static unsigned long timerStart = 0;
  static boolean isNotComplete = false;

  // Serial Read
  while (Serial1.available()) {
    int incoming = Serial1.read();
    if (incoming != '\r' && incoming != '\n') {
      line[letterNo] = incoming;
      letterNo++;
      isNotComplete = true;
      timerStart = millis();
    }
    else if (letterNo != 0) {
      line[letterNo] = '\0';
      sprintf(incomingLine, line);
      letterNo = 0;
      isNotComplete = false;
      return PASS;
    }
  }

  // timeout check
  if (isNotComplete && isTimeout(timerStart, SERIAL_TIMEOUT_MS)) {
    line[letterNo] = '\0';
    sprintf(incomingLine, line);
    letterNo = 0;
    isNotComplete = false;
    return TIMEOUT;
  }

  return FAIL;
}


void com1_send(char *c) {
  Serial1.print(c);
}
void com1_sendln(char *c) {
  Serial1.println(c);
}


// Serial2 -------------------------------------------------------
int com2_check(char *incomingLine) {
  static char line[SERIAL_BUFFER_SIZE];
  static int letterNo = 0;
  static unsigned long timerStart = 0;
  static boolean isNotComplete = false;

  // Serial Read
  while (Serial2.available()) {
    int incoming = Serial2.read();
    if (incoming != '\r' && incoming != '\n') {
      line[letterNo] = incoming;
      letterNo++;
      isNotComplete = true;
      timerStart = millis();
    }
    else if (letterNo != 0) {
      line[letterNo] = '\0';
      sprintf(incomingLine, line);
      letterNo = 0;
      isNotComplete = false;
      return PASS;
    }
  }

  // timeout check
  if (isNotComplete && isTimeout(timerStart, SERIAL_TIMEOUT_MS)) {
    line[letterNo] = '\0';
    sprintf(incomingLine, line);
    letterNo = 0;
    isNotComplete = false;
    return TIMEOUT;
  }

  return FAIL;
}


void com2_send(char *c) {
  Serial2.print(c);
}
void com2_sendln(char *c) {
  Serial2.println(c);
}


// Serial3 -------------------------------------------------------
int com3_check(char *incomingLine) {
  static char line[SERIAL_BUFFER_SIZE];
  static int letterNo = 0;
  static unsigned long timerStart = 0;
  static boolean isNotComplete = false;

  // Serial Read
  while (Serial3.available()) {
    int incoming = Serial3.read();
    if (incoming != '\r' && incoming != '\n') {
      line[letterNo] = incoming;
      letterNo++;
      isNotComplete = true;
      timerStart = millis();
    }
    else if (letterNo != 0) {
      line[letterNo] = '\0';
      sprintf(incomingLine, line);
      letterNo = 0;
      isNotComplete = false;
      return PASS;
    }
  }

  // timeout check
  if (isNotComplete && isTimeout(timerStart, SERIAL_TIMEOUT_MS)) {
    line[letterNo] = '\0';
    sprintf(incomingLine, line);
    letterNo = 0;
    isNotComplete = false;
    return TIMEOUT;
  }

  return FAIL;
}


void com3_send(char *c) {
  Serial3.print(c);
}
void com3_sendln(char *c) {
  Serial3.println(c);
}
















// ===============================================================
bool isTimeout(unsigned long start, unsigned long timeout) {
  unsigned long now = millis();
  if (start + timeout < now)
  {
    return (true);
  }
  return (false);
}












