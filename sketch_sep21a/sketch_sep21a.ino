#include <ps2.h>

PS2 kbd(5, 6); //(clk, data)

void kbd_init()
{
  char ack;

  kbd.write(0xff);  // send reset code
  ack = kbd.read();  // byte, kbd does self test
  ack = kbd.read();  // another ack when self test is done
}

void setup()
{
  Serial.begin(115200);
  kbd_init();
}

/*
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
    Serial.println(code, HEX);
   // delay(20);  /* twiddle */
  }
}
