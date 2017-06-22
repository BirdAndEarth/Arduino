

#define PASS      0
#define FAIL     -1
#define TIMEOUT  -2

#define SERIAL_BUFFER_SIZE  255


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(33, OUTPUT);
  digitalWrite(33, HIGH);
}

void loop() {
  char cRead[255];

  if (serialCheck1(cRead)) {

    Serial.print(cRead);
  }
}



// Serial 1 -------------------------------------------

int serialCheck1(char *cReturn)
{
  static char serialIncoming[255];
  static long st;

  while (Serial1.available()) {
    int  incoming = Serial1.read();

    // Ignore terminate characters
    if (incoming != '\r' && incoming != '\n')
    {
      strcat(serialIncoming, incoming);
    }

    // When detect terminate character
    if (incoming == '\n'))
    {
      sprintf(cReturn, serialIncoming);
      // clear the string:
      serialIncoming[0] = '\0';
      return true;
    }
  }
  return false;
}

boolean timeOutCheck(unsigned long start, unsigned long timeout)
{




}


