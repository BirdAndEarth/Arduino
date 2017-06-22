#include "ps2dev.h" // to emulate a PS/2 device
#include <Wire.h> // to communicate over the I2C port
#include <string.h>
#include <math.h>
#undef int
#include <stdio.h>

uint8_t outbuf[6]; // array to store arduino input
int cnt = 0;
int ledPin = 13;

PS2dev keyboard(3, 2); // PS2dev object (2:data, 3:clock)
int enabled = 0; // pseudo variable for state of "keyboard"

int joy_x_axis; //byte 1
int joy_y_axis; //byte 2
int accel_x_axis; //byte 3
int accel_y_axis; //byte 4
int accel_z_axis; //byte 5
int z_button = 0;
int c_button = 0;
int roll = 0;
int pitch = 0;

void ack() {
  //acknowledge commands
  while (keyboard.write(0xFA));
}


int keyboardcommand(int command) {
  unsigned char val;
  switch (command) {
    case 0xFF: //reset
      ack();
      //the while loop lets us wait for the host to be ready
      while (keyboard.write(0xAA) != 0);
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
      keyboard.read(&val); //do nothing with the rate
      ack();
      break;
    case 0xF2: //get device id
      ack();
      keyboard.write(0xAB);
      keyboard.write(0x83);
      break;
    case 0xF0: //set scan code set
      ack();
      keyboard.read(&val); //do nothing with the rate
      ack();
      break;
    case 0xEE: //echo
      //ack();
      keyboard.write(0xEE);
      break;
    case 0xED: //set/reset LEDs
      ack();
      keyboard.read(&val); //do nothing with the rate
      ack();
      break;
  }
}

void setup() {
  Wire.begin (); // join i2c bus with address 0x52
  nunchuck_init (); // send the initilization handshake
  delay(2000); //initialization time just in case
  // send the keyboard start up
  while (keyboard.write(0xAA) != 0);
}

void nunchuck_init ()
{
  Wire.beginTransmission (0x52);// transmit to device 0x52
  Wire.send (0x40);  // sends memory address
  Wire.send (0x00);  // sends sent a zero.
  Wire.endTransmission (); // stop transmitting
}

void send_zero ()
{
  Wire.beginTransmission (0x52);// transmit to device 0x52
  Wire.send (0x00);  // sends one byte
  Wire.endTransmission (); // stop transmitting
}

void loop() {
  Wire.requestFrom (0x52, 6); // request data from nunchuck
  while (Wire.available ())
  {
    outbuf[cnt] = nunchuk_decode_byte (Wire.receive ());
    // receive byte as an integer
    digitalWrite (ledPin, HIGH); // sets the LED on
    cnt++;
  }

  // If we recieved the 6 bytes, then go process them
  if (cnt >= 5)
  {
    process ();
  }

  unsigned char c;
  //if host device wants to send a command:
  if ( (digitalRead(3) == LOW) || (digitalRead(2) == LOW)) {
    while (keyboard.read(&c)) ;
    keyboardcommand(c);
  }
  else { //send keypresses accordingly using scancodes
    if (joy_y_axis > 198) {
      keyboard.write(0x1D);
    }
    else {
      keyboard.write(0xF0);
      keyboard.write(0x1D);
    }

    if (joy_y_axis < 68) {
      keyboard.write(0x1B);
    }
    else {
      keyboard.write(0xF0);
      keyboard.write(0x1B);
    }

    if (joy_x_axis < 58) {
      keyboard.write(0x1C);
    }
    else {
      keyboard.write(0xF0);
      keyboard.write(0x1C);
    }

    if (joy_x_axis > 190) {
      keyboard.write(0x23);
    }
    else {
      keyboard.write(0xF0);
      keyboard.write(0x23);
    }


    if (pitch < 65) {
      keyboard.write(0x43);
    }
    else {
      keyboard.write(0xF0);
      keyboard.write(0x43);
    }

    if (pitch > 115) {
      keyboard.write(0x42);
    }
    else {
      keyboard.write(0xF0);
      keyboard.write(0x42);
    }

    if (roll > 125 ) {
      keyboard.write(0x3B);
    }
    else {
      keyboard.write(0xF0);
      keyboard.write(0x3B);
    }

    if (roll < 55) {
      keyboard.write(0x4B);
    }
    else {
      keyboard.write(0xF0);
      keyboard.write(0x4B);
    }


    if (!z_button) {
      keyboard.write(0x29);
    }
    else {
      keyboard.write(0xF0);
      keyboard.write(0x29);
    }

    if (!c_button) {
      keyboard.write(0x12);
    }
    else {
      keyboard.write(0xF0);
      keyboard.write(0x12);
    }
  }

  cnt = 0;
  send_zero (); // send the request for next bytes
  delay (10);
}


void process () {
  joy_x_axis = outbuf[0]; //byte 1
  joy_y_axis = outbuf[1]; //byte 2
  accel_x_axis = outbuf[2] * 2 * 2; //byte 3
  accel_y_axis = outbuf[3] * 2 * 2; //byte 4
  accel_z_axis = outbuf[4] * 2 * 2; //byte 5

  z_button = 0;
  c_button = 0;

  roll = 0;
  pitch = 0;
  // byte outbuf[5] contains bits for z and c buttons
  // it also contains the least significant bits for the accelerometer data
  // so we have to check each bit of byte outbuf[5]
  if ((outbuf[5] >> 0) & 1) //'&1' to see only LSB after left shifts
  {
    z_button = 1; //bit 0
  }
  if ((outbuf[5] >> 1) & 1)
  {
    c_button = 1; //bit 1
  }

  if ((outbuf[5] >> 2) & 1)
  {
    accel_x_axis += 1;
  }
  if ((outbuf[5] >> 3) & 1)
  {
    accel_x_axis += 2;
  }

  if ((outbuf[5] >> 4) & 1)
  {
    accel_y_axis += 1;
  }
  if ((outbuf[5] >> 5) & 1)
  {
    accel_y_axis += 2;
  }

  if ((outbuf[5] >> 6) & 1)
  {
    accel_z_axis += 1;
  }
  if ((outbuf[5] >> 7) & 1)
  {
    accel_z_axis += 2;
  }

  //out here the values 499, 518 and 216.0 might differ
  //due to the slight differences nunchucks
  roll = (atan2( (accel_z_axis - 499), (accel_x_axis - 515) ) / 3.14159 * 180);
  pitch = (acos( (accel_y_axis - 518) / 216.0 ) / 3.14159 * 180);
}


// Encode data to format that most wiimote drivers except
// only needed if you use one of the regular wiimote drivers
char nunchuk_decode_byte (char x)
{
  x = (x ^ 0x17) + 0x17;
  return x;
}

