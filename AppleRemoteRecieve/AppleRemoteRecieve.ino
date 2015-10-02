#include "dv32u.h"

#define IR_PIN  PD0
#define LED_PIN PC7


// The following variables for the remote control feature
int duration;         // Duration of the IR pulse
int mask;
int c1;               // Byte 1 of the 32-bit remote command code
int c2;               // Byte 2 of the 32-bit remote command code
int c3;               // Byte 3 of the 32-bit remote command code
int c4;               // Byte 4 of the 32-bit remote command code
int IRkey;            // The unique code (Byte 3) of the remote key
int previousIRkey;    // The previous code (used for repeat)


void setup(){
  pinMode(IR_PIN, INPUT);      // Pin for IR sensor
  digitalWrite(IR_PIN, HIGH);  // Enable pull-up resistor
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(IR_PIN, HIGH);      
  delay(100);
  digitalWrite(IR_PIN, LOW);

  Serial.begin(115200);

}

void loop() {

  /*
  The following code is for the remote control. It handles the codes generated by the Apple remote
   control except 0 has been designated for "repeat" and 255 designated as an error code. The current
   Apple remote does not generate these codes.
   */

  while(digitalRead(IR_PIN) == LOW){

    if((IRkey = getIRkey()) == 255){
      // Do nothing
    }
    else if(IRkey == 0){  // Repeat
 //     IRkey=previousIRkey;
    }
    else {  // New command
      previousIRkey = IRkey;
    }

    switch(IRkey){
    case 11:  // 11 and 10 are the up key
    case 10:
      Serial.println("Up");
      Keyboard.begin();
      Keyboard.write(KEY_UP_ARROW); 
      Keyboard.end();

      break;

    case 13:  // 13, 12 are the down key
    case 12:    
      Serial.println("Down");
      Keyboard.begin();
      Keyboard.write(KEY_DOWN_ARROW); 
      Keyboard.end();
      break;

    case 8:  // 8, 9 are the left key
    case 9:
      Serial.println("Left");
      Keyboard.begin();
      Keyboard.write(KEY_LEFT_ARROW); 
      Keyboard.end();
      break;

    case 7:  // 7, 6 are the right key
    case 6:
      Serial.println("Right");
      Keyboard.begin();
      Keyboard.write(KEY_RIGHT_ARROW); 
      Keyboard.end();
      break;

    case 2:  // 2, 3 are the menu key
    case 3:
      Serial.println("Menu");
      Keyboard.begin();
      Keyboard.write(KEY_LEFT_ARROW); 
      Keyboard.end();

      break;

    case 94:  // 94, 95 are the palypause key
    case 95:
      Serial.println("PlayPause");
      Keyboard.begin();
      Keyboard.write(KEY_RIGHT_ARROW); 
      Keyboard.end();

      break;

    case 93:  // 93, 92 are the center key
    case 92:
      Serial.println("Center");
      Keyboard.begin();
      Keyboard.write(KEY_RIGHT_ARROW); 
      Keyboard.end();
      break;

    case 4:   // 4, 5 are the backword compatibility for White Apple Remote's Center(PlayPause) key.
    case 5:
      break;

    default:
      break;    
    }

//        Serial.print(IRkey);
//       Serial.println(" ");


  } // End of remote control code

}


/************************ IR RECIEVE ************************************************************/


/*
 The following fucntion defines a new pulseIn function because the pulseIn function in the Arduino
 library does not exit if there is a pulse that does not end. Typically, this would not cause any
 problems if you are reading true pulses, but because the remote code I wrote measures "UP pulses"
 there is a chance that some noise would trigger a sinle pulse where the current pulseIn function
 would hang.
 The reason is the following: the IR receiver when it is not receiving any signals outputs HIGH.
 If there is a signal (a real pulse), it outputs LOW and then HIGH. If I were to measure DOWN putlses,
 this would be fine, but because the NEC protocol in the Apple remote uses distance between pulses to
 codify its information, I measure the time between pulses which is an "UP pulse". In reality these UP
 pulses are not really pulses, but the time between the real pulses from the remote control.
 This code is taken from the Arduino code base (thanks to users in the Arduino forum) and modified to
 check for end of pulse
 */

unsigned long newpulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
  uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);
  uint8_t stateMask = (state ? bit : 0);
  unsigned long width = 0;

  unsigned long numloops = 0;
  unsigned long maxloops = microsecondsToClockCycles(timeout) / 16;

  // wait for any previous pulse to end
  while ((*portInputRegister(port) & bit) == stateMask)
    if (numloops++ == maxloops)
      return 0;

  // wait for the pulse to start
  while ((*portInputRegister(port) & bit) != stateMask)
    if (numloops++ == maxloops)
      return 0;

  // wait for the pulse to stop
  while ((*portInputRegister(port) & bit) == stateMask){
    if(width++ == maxloops)  // added the check for end of pulse
      return 0;
  }
  return clockCyclesToMicroseconds(width * 20+16); // Recalibrated because of additional code
  // in the width loop
} 

/*
 The following function returns the code from the Apple Aluminum remote control. The Apple remote is
 based on the NEC infrared remote protocol. Of the 32 bits (4 bytes) coded in the protocol, only the
 third byte corresponds to the keys. The function also handles errors due to noise (returns 255) and
 the repeat code (returs zero)
 
 The Apple remote returns the following codes:
 
 Up key:     238 135 011 089
 Down key:   238 135 013 089
 Left key:   238 135 008 089
 Right key:  238 135 007 089
 Center key: 238 135 093 089 followed by 238 135 004 089 (don't know why there is two commands)
 Menu key:   238 135 002 089
 Play key:   238 135 094 089 followed by 238 135 004 089 (don't know why there is two commands)
 */

int getIRkey() {
  c1 = 0;
  c2 = 0;
  c3 = 0;
  c4 = 0;
  duration = 1;
  while((duration = newpulseIn(IR_PIN, HIGH, 15000)) < 2000 && duration != 0)
  {
    // Wait for start pulse
  }
  if (duration == 0)          // This is an error no start or end of pulse
    return(255);              // Use 255 as Error

  else if (duration < 3000)   // This is the repeat
    return (0);               // Use zero as the repeat code

  else if (duration < 5000){  // This is the command get the 4 byte
    mask = 1;				    
    for (int i = 0; i < 8; i++){	             // get 8 bits
      if(newpulseIn(IR_PIN, HIGH, 3000) > 1000)      // If "1" pulse
        c1 |= mask;			             // Put the "1" in position
      mask <<= 1;				     // shift mask to next bit
    }
    mask = 1;				    
    for (int i = 0; i < 8; i++){	             // get 8 bits
      if(newpulseIn(IR_PIN, HIGH, 3000) > 1000)      // If "1" pulse
        c2 |= mask;			             // Put the "1" in position
      mask <<= 1;				     // shift mask to next bit
    }
    mask = 1;				    
    for (int i = 0; i < 8; i++){	             // get 8 bits
      if(newpulseIn(IR_PIN, HIGH, 3000) > 1000)      // If "1" pulse
        c3 |= mask;			             // Put the "1" in position
      mask <<= 1;				     // shift mask to next bit
    }
    mask = 1;				    
    for (int i = 0; i < 8; i++){	             // get 8 bits
      if(newpulseIn(IR_PIN, HIGH, 3000) > 1000)      // If "1" pulse
        c4 |= mask;			             // Put the "1" in position
      mask <<= 1;				     // shift mask to next bit
    }
//         Serial.print(c1, HEX); //For debugging
//         Serial.print(" ");     //For debugging
//         Serial.print(c2, HEX); //For debugging
//         Serial.print(" ");     //For debugging
//         Serial.print(c3, HEX); //For debugging
//         Serial.print(" ");     //For debugging
//         Serial.print(c4, HEX); //For debugging
//         Serial.println("");     //For debugging

    return(c3);
  }
}






