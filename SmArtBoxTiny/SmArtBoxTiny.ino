/*****************************************
 *  SmArtBoxTiny for SmArt! Box ATTiny85
 *                         Rev. 1.0 shiu
 ******************************************/

#define BOOT_MODE      0
#define ACTIVE_MODE    1
#define REBOOT_MODE    2
#define SHUTDOWN_MODE  3

/* for ATTiny */
int sw1Pin = 3;
int sw2Pin = 4;
int livePin = 1;
int outPin = 0;
int relayPin = 2;

/* for Arduino Uno Debbuging */
//int sw1Pin = 7;
//int sw2Pin = 10;
//int livePin = 12;
//int outPin = 13;
//int relayPin = 11;
//int gnd1Pin = 5;
//int gnd2Pin = 8;

int mode = 0;
int gsw1State = 0;
int gsw2State = 0;
int timeInterval = 50; //ms
int timePress = 100;
int timePressLong = 1000;

unsigned long timeSw1Pressed = 0;
unsigned long timeSw2Pressed = 0;

void setup() {
  //  pinMode(sw1Pin, INPUT_PULLUP); //dbg
  //  pinMode(sw2Pin, INPUT_PULLUP); //dbg

  pinMode(sw1Pin, INPUT);
  pinMode(sw2Pin, INPUT);

  pinMode(livePin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(outPin, OUTPUT);


  //  pinMode(gnd1Pin, OUTPUT); // for dbg
  //  pinMode(gnd2Pin, OUTPUT); // for dbg
  //  digitalWrite(gnd1Pin, LOW); // for dbg
  //  digitalWrite(gnd2Pin, LOW); // for dbg

  digitalWrite(outPin, LOW);
  digitalWrite(relayPin, LOW);
  //  Serial.begin(115200);
}


void loop() {
//  modeCheck();
  checkButtons();

  switch (mode) {
  case BOOT_MODE:
    bootMode();
    break;
  case ACTIVE_MODE:
    activeMode();
    break;
  case REBOOT_MODE:
    rebootMode();
    break;
  case SHUTDOWN_MODE:
    shutdownMode();
    break;
  }  
}


void modeCheck() {
  if (digitalRead(livePin) == LOW) {
    mode = BOOT_MODE; 
  }
  else {
    mode = ACTIVE_MODE;
  }
}


void bootMode(){
  if (gsw2State == 2) {
    digitalWrite(relayPin, HIGH);
    //    Serial.println("BOOT!");
    gsw2State = 0;
    delay(10000);
  }
  if (digitalRead(livePin) == HIGH) {
    //    Serial.println("Raspi Booted!");
    mode = ACTIVE_MODE;
  }
}


void activeMode(){
  if (gsw1State == 2) {
    Serial.println("REBOOT!");
    gsw1State = 0;
    mode = REBOOT_MODE;
  }
  if (gsw2State == 2) {
    Serial.println("SHUTDOWN!");
    gsw2State = 0;
    mode = SHUTDOWN_MODE;
  }
}

void rebootMode() {
  digitalWrite(outPin, HIGH);
  delay(100);
  digitalWrite(outPin, LOW);
  gsw1State = 0;
  gsw2State = 0;

  mode = BOOT_MODE;
}

void shutdownMode() {
  digitalWrite(outPin, HIGH);
  delay(500);
  digitalWrite(outPin, LOW);
  gsw1State = 0;
  gsw2State = 0;
  while(1) {
    if (digitalRead(livePin) == LOW) {
      break;
    }
    delay(10);  
  }
  delay(10000);
  digitalWrite(relayPin, LOW);

  mode = BOOT_MODE;
}


void checkButtons() {
  static unsigned long timeNow = 0;
  static unsigned long timeOld = 0;
  static boolean sw1oldstate = false;
  static boolean sw2oldstate = false;
  boolean sw1state = false;
  boolean sw2state = false;
  static boolean sw1LongPressedFlg = false;
  static boolean sw2LongPressedFlg = false;

  gsw1State = 0;
  gsw2State = 0;

  timeNow = millis();
  if ((timeNow - timeOld) > timeInterval){
    sw1state = !digitalRead(sw1Pin);
    sw2state = !digitalRead(sw2Pin);

    // Pressed
    if (!sw1oldstate && sw1state) {
      timeSw1Pressed = timeNow;
    } 
    if (!sw2oldstate && sw2state) {
      timeSw2Pressed = timeNow;
    }

    // Release
    if (sw1oldstate && !sw1state) {
      sw1Released();
      if (timeNow - timeSw1Pressed > timePress && !sw1LongPressedFlg) {
        sw1Pressed();
      } 
      timeSw1Pressed = 0;
      sw1LongPressedFlg = false;
    } 
    if (sw2oldstate && !sw2state) {
      sw2Released();
      if (timeNow - timeSw2Pressed > timePress && !sw2LongPressedFlg) {
        sw2Pressed();
      } 
      timeSw2Pressed = 0;
      sw2LongPressedFlg = false;
    }

    // Pressing
    if (sw1state && (timeSw1Pressed != 0)) {
      if (timeNow - timeSw1Pressed > timePressLong) {
        sw1LongPressed();
        sw1LongPressedFlg = true;
        timeSw1Pressed = 0;
      }
    }
    if (sw2state && (timeSw2Pressed != 0)) {
      if (timeNow - timeSw2Pressed > timePressLong) {
        sw2LongPressed();
        sw2LongPressedFlg = true;
        timeSw2Pressed = 0;
      }
    }

    sw1oldstate = sw1state;
    sw2oldstate = sw2state;
    timeOld = timeNow;
  }
}

void sw1Pressed() {
  //  Serial.println("sw1 Pressed.");
  gsw1State = 1;
}
void sw1LongPressed() {
  //  Serial.println("sw1 Long Pressed.");
  gsw1State = 2;
}
void sw1Released() {
}

void sw2Pressed() {
  //  Serial.println("sw2 Pressed.");
  gsw2State = 1;
}
void sw2LongPressed() {
  //  Serial.println("sw2 Long Pressed.");
  gsw2State = 2;
}
void sw2Released() {
}






