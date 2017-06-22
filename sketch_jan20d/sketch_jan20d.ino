

boolean blnStringComplete1 = false;   // whether the string is complete
char cSerialIncoming1[255];



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(33, OUTPUT);
  digitalWrite(33, HIGH);
}

void loop() {
  char cRead[255];

  if (serialCheck1()) {
    read1(cRead);
    Serial.print(cRead);
  }
}



// Serial 1 -------------------------------------------

boolean serialCheck1() {
  while (Serial1.available()) {
    char inChar[2];
//    char cBuf[255];
    int  iBuf = Serial1.read();
    sprintf(inChar, "%c", iBuf);

    // Ignore terminate character
    if ((strcmp(inChar, "\r") && strcmp(inChar, "\n"))) {
      strcat(cSerialIncoming1, inChar);
    }

   // Ignore terminate character
      strcat(cSerialIncoming1, inChar);

    // Detect terminate character
    if (!strcmp(inChar, "\n")) {
      blnStringComplete1 = true;
      return true;
    }
  }
  return false;
}

void read1(char *cReturn) {
  cReturn[0] = '\0';
  if (blnStringComplete1) {
    sprintf(cReturn, cSerialIncoming1);
    // clear the string:
    cSerialIncoming1[0] = '\0';
    blnStringComplete1 = false;
  }
  return;

}

