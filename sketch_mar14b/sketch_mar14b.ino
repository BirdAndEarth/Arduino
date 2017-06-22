
int sckPin = 30;
int latchPin = 31;
int dataPin = 28;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(sckPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {


  for (byte data = 0; data < 256; data++) {

    digitalWrite(latchPin, 0);
    shiftOut(dataPin, sckPin, MSBFIRST, data);
    shiftOut(dataPin, sckPin, MSBFIRST, 0);
    shiftOut(dataPin, sckPin, MSBFIRST, 0);
    
    digitalWrite(latchPin, 1);

  }

}


