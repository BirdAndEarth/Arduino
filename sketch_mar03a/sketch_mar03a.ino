int led = 33;
int but = 32;
int i1 = 14;
int i2 = 13;
int i3 = 12;
int i4 = 11;
int i5 = 10;
int i6 = 9;

volatile int bLED = LOW;

void interruptFunction() {
  bLED = !bLED;
}

void interruptFunction1() {
  bLED = !bLED;
}
void interruptFunction2() {
  bLED = !bLED;
}
void interruptFunction3() {
  bLED = !bLED;
}
void interruptFunction4() {
  bLED = !bLED;
}
void interruptFunction5() {
  bLED = !bLED;
}
void interruptFunction6() {
  bLED = !bLED;
}


void setup() {
  pinMode(led, OUTPUT);
  pinMode(but, INPUT_PULLDOWN);
  pinMode(i1, INPUT_PULLUP);
  pinMode(i2, INPUT_PULLUP);
  pinMode(i3, INPUT_PULLUP);
  pinMode(i4, INPUT_PULLUP);
  pinMode(i5, INPUT_PULLUP);
  pinMode(i6, INPUT_PULLUP);

  attachInterrupt(but, interruptFunction, CHANGE);
  attachInterrupt(i1, interruptFunction1, FALLING);
  attachInterrupt(i2, interruptFunction2, FALLING);
  attachInterrupt(i3, interruptFunction3, FALLING);
  attachInterrupt(i4, interruptFunction4, FALLING);
  attachInterrupt(i5, interruptFunction5, FALLING);
  attachInterrupt(i6, interruptFunction6, FALLING);

}

void loop() {
  digitalWrite(led, bLED);
}
