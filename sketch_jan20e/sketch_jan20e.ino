



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(33, OUTPUT);
  digitalWrite(33, HIGH);
}

void loop() {
  char cRead[255];

  if (serial1Check(cRead)) {

    Serial.println(cRead);
  }
}



// Serial 1 -------------------------------------------

boolean serialCheck1(char *incomingLine) {
  // static boolean blnStringComplete1 = false;   // whether the string is complete
  static char line[255];

  while (Serial1.available()) {
    char inChar[2];
    int  incoming = Serial1.read();
    sprintf(inChar, "%c", incoming);

    // Ignore terminate character
    if ((strcmp(inChar, "\r") && strcmp(inChar, "\n"))) {
      strcat(line, inChar);
    }

    // Detect terminate character
    if (!strcmp(inChar, "\n")) {
      // blnStringComplete1 = true;
      incomingLine[0] = '\0';
      // if (blnStringComplete1) {
      sprintf(incomingLine, line);
      // clear the string:
      line[0] = '\0';
      // }
      return true;
    }
  }
  return false;
}

boolean serial1Check(char *incomingLine)
{
  static char line[255];
  static int letterNo = 0;

  while (Serial1.available()) {
    int incoming = Serial1.read();

    // Ignore terminate character
    if (incoming != '\r' && incoming != '\n')
    {
      line[letterNo] = incoming;
      letterNo++;
    }
    else
    {
      line[letterNo] = '\0';
      sprintf(incomingLine, line);
      letterNo = 0;
      return true;
    }
  }
  return false;
}
