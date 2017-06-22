//=================================================
// Multiple Serial For Maple Mini
//                 Rev. 1 16/01/21 shiu
//
//=================================================

/*
    UART1 <-THRU-> UART2
    UART3 is Monitor out
*/


#define PASS     1
#define FAIL    -1
#define TIMEOUT -2

#define SERIAL_BUFFER_SIZE   1024
#define SERIAL_TIMEOUT_MS    5000
#define COM_BAUD_RATE        9600
#define COM1_BAUD_RATE       1200
#define COM2_BAUD_RATE       1200
#define COM3_BAUD_RATE       9600


int com1_baud;
int com1_config;
int com2_baud;
int com2_config;
int recieveBefore = 0;
unsigned long com1_last_sent  = 0;
unsigned long com2_last_sent  = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(1200);
  Serial2.begin(1200);
  Serial3.begin(9600);

  //  com_sendln("com ready");
  //  com1_sendln("com1 ready");
  //  com2_sendln("com2 ready");
  //  com3_sendln("com3 ready");



}

void loop() {
  char com_incomingLine[SERIAL_BUFFER_SIZE];
  char com1_incomingLine[SERIAL_BUFFER_SIZE];
  char com2_incomingLine[SERIAL_BUFFER_SIZE];
  char com3_command[SERIAL_BUFFER_SIZE];







  // Serial1
  switch (com1_check(com1_incomingLine)) {
    case PASS:
      if (recieveBefore != 1) {
        com_send("\n   --");
        char c[16];
        sprintf(c, "%d",millis() - com1_last_sent);
        com_send(c);
        com_send("ms--\n[1]");
      }
      com_send(com1_incomingLine);
      recieveBefore = 1;
      com1_last_sent = millis();

      break;
    case FAIL:
      break;
    case TIMEOUT:
      break;
  }


  // Serial2
  switch (com2_check(com2_incomingLine)) {
    case PASS:
      if (recieveBefore != 2) {
        com_send("\n   --");
        char c[16];
        sprintf(c, "%d", millis() - com1_last_sent);
;        com_send(c);
        com_send("ms--\n[2]");
      }
      com_send(com2_incomingLine);
      recieveBefore = 2;
      com2_last_sent = millis();
      break;
    case FAIL:
      break;
    case TIMEOUT:
      break;
  }


  // Serial3
  switch (com3_check(com1_incomingLine)) {
    case PASS:
      break;
    case FAIL:
      break;
    case TIMEOUT:
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

    if (incoming == '\r')
    {
      line[letterNo] = '<' ; letterNo++;
      line[letterNo] = 'C' ; letterNo++;
      line[letterNo] = 'R' ; letterNo++;
      line[letterNo] = '>' ; letterNo++;
    }
    if (incoming == '\n')
    {
      line[letterNo] = '<' ; letterNo++;
      line[letterNo] = 'L' ; letterNo++;
      line[letterNo] = 'F' ; letterNo++;
      line[letterNo] = '>' ; letterNo++;
    }

    if (incoming != '\r' && incoming != '\n') {
      line[letterNo] = incoming;
      letterNo++;
      isNotComplete = true;
      timerStart = millis();
    }
    else
    {


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

/* *****************************
    Serial1 THRU to Serial2
 * ***************************** */
int com1_check(char *incomingLine) {
  static char line[SERIAL_BUFFER_SIZE];
  static int letterNo = 0;
  static unsigned long timerStart = 0;
  static boolean isNotComplete = false;

  // Serial Read
  while (Serial1.available()) {
    int incoming = Serial1.read();

    // send thru to Serial2
    Serial2.write(incoming);

    // detect terminate char etc...
    if (incoming != '\r' && incoming != '\n') {
      line[letterNo] = incoming;
      letterNo++;
    }

    if (incoming == '\r')
    {
      line[letterNo] = '<' ; letterNo++;
      line[letterNo] = 'C' ; letterNo++;
      line[letterNo] = 'R' ; letterNo++;
      line[letterNo] = '>' ; letterNo++;
    }
    if (incoming == '\n')
    {
      line[letterNo] = '<' ; letterNo++;
      line[letterNo] = 'L' ; letterNo++;
      line[letterNo] = 'F' ; letterNo++;
      line[letterNo] = '>' ; letterNo++;
    }

    line[letterNo] = '\0';
    sprintf(incomingLine, line);
    letterNo = 0;
    return PASS;
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
/* *****************************
    Serial2 THRU to Serial1
 * ***************************** */
int com2_check(char *incomingLine) {
  static char line[SERIAL_BUFFER_SIZE];
  static int letterNo = 0;
  static unsigned long timerStart = 0;
  static boolean isNotComplete = false;

  // Serial Read
  while (Serial2.available()) {
    int incoming = Serial2.read();

    // send thru to Serial1
    Serial1.write(incoming);

    // detect terminate char etc...
    if (incoming != '\r' && incoming != '\n') {
      line[letterNo] = incoming;
      letterNo++;
    }

    if (incoming == '\r')
    {
      line[letterNo] = '<' ; letterNo++;
      line[letterNo] = 'C' ; letterNo++;
      line[letterNo] = 'R' ; letterNo++;
      line[letterNo] = '>' ; letterNo++;
    }
    if (incoming == '\n')
    {
      line[letterNo] = '<' ; letterNo++;
      line[letterNo] = 'L' ; letterNo++;
      line[letterNo] = 'F' ; letterNo++;
      line[letterNo] = '>' ; letterNo++;
    }

    line[letterNo] = '\0';
    sprintf(incomingLine, line);
    letterNo = 0;
    return PASS;
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












