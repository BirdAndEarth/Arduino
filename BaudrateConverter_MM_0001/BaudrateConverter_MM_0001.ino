/*******************************************************************
  Baudrate Converter for KPI 20.207.A board

  to TESTER = Serial3
  to SYSTEM = Serial2

  ----------------------------------------------------------------
  ver   date        Author  Description
  0000  2017/02/28  SY      New.

********************************************************************/
#define DBG               0
#define TESTER_BAUDRATE   115200
#define SYSTEM_BAUDRATE   9600
int ledDataPin = 14;
int ledPin = 33;
int dbg = 1;

/*******************************************************************
 PINs
********************************************************************/
void pinInit() {
  pinMode(ledDataPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  ledOff();
}


void ledOn() {
  digitalWrite(ledPin, HIGH);
  digitalWrite(ledDataPin, LOW);
}
void ledOff() {
  digitalWrite(ledPin, LOW);
  digitalWrite(ledDataPin, HIGH);
}



/*******************************************************************
 SERIALs
********************************************************************/
void serialInit() {

# if DBG
  Serial.begin(115200);
# endif

  // SYSTEM SIDE
  Serial2.begin(SYSTEM_BAUDRATE);

  // TESTER SIDE
  Serial3.begin(TESTER_BAUDRATE);

}

void serialIncomingCheck2() {
  while (Serial2.available()) {
    ledOn();
//    char inChar = (char)Serial2.read();
//    Serial3.print(inChar);

    int inChar = Serial2.read();
    Serial3.write(inChar);


#if DBG
    Serial.print("SYSTEM>");
    Serial.println((char)inChar);
#endif
  }
  ledOff();
}

void serialIncomingCheck3() {
  while (Serial3.available()) {
    ledOn();
//    char inChar = (char)Serial3.read();
//    Serial2.print(inChar);
    int inChar = Serial3.read();
    Serial2.write(inChar);

#if DBG
    Serial.print("TESTER>");
    Serial.println((char)inChar);
    
#endif
  }
  ledOff();
}

/*******************************************************************
 SETUP
********************************************************************/
void setup() {
  pinInit();
  serialInit();
}

/*******************************************************************
 LOOP
********************************************************************/
void loop() {
  serialIncomingCheck2();
  serialIncomingCheck3();
}
