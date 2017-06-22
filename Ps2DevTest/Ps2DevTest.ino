#include <ps2dev.h>

#define CLK_PIN  3
#define DATA_PIN 2

/* Serials */
String strSeriaIncoming = "";         // a string to hold incoming data
String strSeriaIncomingUSB = "";         // a string to hold incoming data

boolean blnStringComplete = false;  // whether the string is complete
boolean blnStringCompleteUSB = false;  // whether the string is complete





/* PS2 kbdEmu */
PS2dev kbdEmu(CLK_PIN, DATA_PIN); // PS2dev object (2:data, 3:clock)
int enabled = 0; // pseudo variable for state of "kbdEmu"





void ack() {
  //acknowledge commands
  while (kbdEmu.write(0xFA));
}

int kbdEmucommand(int command) {
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
void serialInit() {
  // initialize serial:
  Serial.begin(115200);
  SerialUSB.begin(115200);

  // reserve 200 bytes for the strSeriaIncoming1:
  strSeriaIncoming.reserve(200);
  strSeriaIncomingUSB.reserve(200);

}


void serialCheck() {
  serialIncomingCheck();
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
/* ------------------------------------------------------------*/



/* DEBUG ----------------------------------------------------  */
void dbg(String text) {
  SerialUSB.print(millis());
  SerialUSB.print('\t');
  SerialUSB.print(text);
}
void dbgln(String text) {
  Serial1.print(millis());
  Serial1.print('\t');
  SerialUSB.println(text);
}
/* ------------------------------------------------------------*/





/* SET UP */
void setup() {
  serialInit();

}


/* LOOP */
void loop() {
  // put your main code here, to run repeatedly:
  serialCheck();
}




















