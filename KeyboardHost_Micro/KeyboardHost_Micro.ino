#include "dv32u.h"

#include <ps2.h>

/*
 * an arduino sketch to interface with a ps/2 keyboard.
 * Also uses serial protocol to talk back to the host
 * and report what it finds. Used the ps2 library.
 */



/*
 * Pin 5 is the ps2 data pin, pin 6 is the clock pin
 * Feel free to use whatever pins are convenient.

 Keyboard pinouts
MINI DIN 6 (male)
   1   data
   3   gnd
   4   +5v
   5   clock



 */

PS2 kbd(PD7, PD6); //(clk, data)

void kbd_init()
{
  char ack;

  kbd.write(0xff);  // send reset code
  ack = kbd.read();  // byte, kbd does self test
  ack = kbd.read();  // another ack when self test is done
}

void setup()
{
  //  Serial.begin(115200);
  Serial1.begin(115200);
  kbd_init();
}

/*2
 * get a keycode from the kbd and report it back to the
 * host via the serial line.
 */
void loop()
{
  unsigned char code;

  for (;;) { /* ever */
    /* read a keycode */
    code = kbd.read();
    /* send the data back up */
    //    Serial.println(code, HEX);
    Serial1.write(code);
    delay(1);  /* twiddle */
  }
}
