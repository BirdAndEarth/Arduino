/*************************************
SSIF TEST Program for Arduino UNO
150917 Shiu
*************************************/


// Pins
int in1pin =  8; // to I/F OUT1
int in2pin =  9; // to I/F OUT2
int in3pin = 10; // to I/F OUT3
int in4pin = 11; // to I/F OUT4

int out1pin = 4; // to I/F IN1
int out2pin = 5; // to I/F IN2
int out3pin = 6; // to I/F IN3
int out4pin = 7; // to I/F IN4





void setup() {

  pinMode(in1pin, INPUT_PULLUP);
  pinMode(in2pin, INPUT_PULLUP);
  pinMode(in3pin, INPUT_PULLUP);
  pinMode(in4pin, INPUT_PULLUP);

  pinMode(out1pin, OUTPUT);
  pinMode(out2pin, OUTPUT);
  pinMode(out3pin, OUTPUT);
  pinMode(out4pin, OUTPUT);

  digitalWrite(out1pin, LOW);
  digitalWrite(out2pin, LOW);
  digitalWrite(out3pin, LOW);
  digitalWrite(out4pin, LOW);

}

void loop() {

}
