#include <oddebug.h>
#include <usbconfig-prototype.h>
#include <usbconfig.h>
#include <usbdrv.h>
#include <UsbKeyboard.h>
#include <usbportability.h>

#include "UsbKeyboard.h"

#define BUTTON_PIN 17

// If the timer isr is corrected
// to not take so long change this to 0.
#define BYPASS_TIMER_ISR 1

boolean buttonState = false;


void setup() {
  pinMode(BUTTON_PIN, INPUT);

#if BYPASS_TIMER_ISR
  // disable timer 0 overflow interrupt (used for millis)
  TIMSK0&=!(1<<TOIE0); // ++
#endif
}

#if BYPASS_TIMER_ISR
void delayMs(unsigned int ms) {
  for (int i = 0; i < ms; i++) {
    delayMicroseconds(1000);
  }
}
#endif

void loop() {

  UsbKeyboard.update();

  //digitalWrite(13, !digitalRead(13));

  if (digitalRead(BUTTON_PIN) == HIGH ) {
    if (!buttonState){
      digitalWrite(13, HIGH);

      //UsbKeyboard.sendKeyStroke(KEY_B, MOD_GUI_LEFT);

      UsbKeyboard.sendKeyStroke(KEY_H);
      UsbKeyboard.sendKeyStroke(KEY_E);
      UsbKeyboard.sendKeyStroke(KEY_L);
      UsbKeyboard.sendKeyStroke(KEY_L);
      UsbKeyboard.sendKeyStroke(KEY_O);

      UsbKeyboard.sendKeyStroke(KEY_SPACE);

      UsbKeyboard.sendKeyStroke(KEY_W);
      UsbKeyboard.sendKeyStroke(KEY_O);
      UsbKeyboard.sendKeyStroke(KEY_R);
      UsbKeyboard.sendKeyStroke(KEY_L);
      UsbKeyboard.sendKeyStroke(KEY_D);
//      //UsbKeyboard.sendKeyStroke(KEY_B, MOD_GUI_LEFT);

      UsbKeyboard.sendKeyStroke(KEY_ENTER);

      buttonState = true;
    }
  }
  else {
    buttonState = false;
  }
#if BYPASS_TIMER_ISR  // check if timer isr fixed.
  delayMs(20);
#else
  delay(5);
#endif
      digitalWrite(13, LOW);

}



