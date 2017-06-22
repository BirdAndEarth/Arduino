#include "dv32u.h"
#include <ps2dev.h>


#define CLK_PIN  PD4
#define DATA_PIN PD0





/* PS2 kbdEmu */
PS2dev kbdEmu(CLK_PIN, DATA_PIN); // PS2dev object (2:data, 3:clock)
int enabled = 0; // pseudo variable for state of "kbdEmu"


void ack() {
  //acknowledge commands
  while (kbdEmu.write(0xFA));
}

int keyboardcommand(int command) {
  unsigned char val;
  switch (command) {
    case 0xFF: //reset
      ack();
      //the while loop lets us wait for the host to be ready
      while (kbdEmu.write(0xAA) != 0);
      break;
    case 0xFE: //resend
      ack();
      break;
    case 0xF6: //set defaults
      //enter stream mode
      ack();
      break;
    case 0xF5: //disable data reporting
      //FM
      enabled = 0;
      ack();
      break;
    case 0xF4: //enable data reporting
      //FM
      enabled = 1;
      ack();
      break;
    case 0xF3: //set typematic rate
      ack();
      kbdEmu.read(&val); //do nothing with the rate
      ack();
      break;
    case 0xF2: //get device id
      ack();
      kbdEmu.write(0xAB);
      kbdEmu.write(0x83);
      break;
    case 0xF0: //set scan code set
      ack();
      kbdEmu.read(&val); //do nothing with the rate
      ack();
      break;
    case 0xEE: //echo
      //ack();
      kbdEmu.write(0xEE);
      break;
    case 0xED: //set/reset LEDs
      ack();
      kbdEmu.read(&val); //do nothing with the rate
      ack();
      break;
  }
}





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
  //Serial.begin(115200);
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
    digitalWrite(PC7, HIGH);
    unsigned char inChar = Serial1.read();
    kbdEmu.write(inChar);
    dbgWriteln(inChar);

    //strSeriaIncoming1 += inChar;
    //if (inChar == '\n') {
    //blnStringComplete1 = true;
    //}
  }
  digitalWrite(PC7, LOW);


}

void serialComplete() {
  // Serial
  if (blnStringComplete) {
    serialCommandRecieve(strSeriaIncoming);
    strSeriaIncoming = "";
    blnStringComplete = false;
  }
  /*
  // Serial1
  if (blnStringComplete1) {
    serialCommandRecieve1(strSeriaIncoming1);
    strSeriaIncoming1 = "";
    blnStringComplete1 = false;
  }
  */
}

void serialCommandRecieve(String command) {
  dbg("Serial<\t" + command);

}
void serialCommandRecieve1(String command) {
  dbg("Serial1<\t" + command);

}

void dbg(String text) {
  //Serial.print(millis());
  //Serial.print('\t');
  //Serial.print(text);
}
void dbgln(String text) {
  //Serial.print(millis());
  //Serial.print('\t');
  //Serial.println(text);
}

void dbgWriteln(unsigned char c) {
  //Serial.print(millis());
  //Serial.print('\t');
  //Serial.println(c, HEX);
}

/* SERIALs END ******************************************************/



/* =======================================================================================
 setup
=========================================================================================== */
void setup() {

  pinMode(PC7, OUTPUT);
  serialInit();


}


/* =======================================================================================
 loop
=========================================================================================== */
void loop() {
  unsigned char c;

  //   if( (digitalRead(3)==LOW) || (digitalRead(2) == LOW)) {
  //    while(kbdEmu.read(&c)) ;
  //    //Serial.println(c,HEX);
  //    keyboardcommand(c);
  //  }


  serialCheck();

}




















