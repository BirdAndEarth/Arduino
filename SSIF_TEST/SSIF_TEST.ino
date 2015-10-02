/*************************************
SSIF TEST Program for Arduino UNO
150917 Shiu
*************************************/


// Pins
int in4pin = 11; // to I/F OUT4
int in3pin = 10; // to I/F OUT3
int in2pin =  9; // to I/F OUT2
int in1pin =  8; // to I/F OUT1

int out4pin = 7; // to I/F IN4
int out3pin = 6; // to I/F IN3
int out2pin = 5; // to I/F IN2
int out1pin = 4; // to I/F IN1





void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);



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

  attachInterrupt(0, sendStart, FALLING); // pin2
  attachInterrupt(1, sendLotClear, FALLING); // pin3


}

void loop() {

  sendStart();

}



void sendStart() {

  digitalWrite(out1pin, LOW);
  digitalWrite(out2pin, HIGH);

  delay(500);
  digitalWrite(out1pin, HIGH);
  digitalWrite(out2pin, LOW);
  delay(500);


}

void sendLotClear() {
  digitalWrite(out2pin, HIGH);
  delay(500);
  digitalWrite(out2pin, LOW);

}
