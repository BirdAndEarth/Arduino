/*******************************************
 * serialReadTest for 0001
 *******************************************/

String strRead;
int mode = 0;


void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  Serial.begin(115200);
//  while(!Serial){
//  }
}

void loop() {
  serialReadLineCheck();
  strRead = serialReadLine();

  if (strRead == "?"){
    delay(3);
    Serial.print("DaVinci32U");
    ledBlink();

  }
  else if (strRead == "s"){
    mode = 1;
    //Serial.println("start");
  }
  else if (strRead == "e"){
    mode = 0;
    //Serial.println("end");
  }


  switch (mode) {
  case 0:
    break;

  case 1:
    test();
    break;

  }   
}



void test(void) {
  static int n = 0;
  Serial.println(n);
  n++;
  delay(100);
}

void ledOn(void) {
  digitalWrite(13, HIGH); 
  delay(100);
}

void ledOff(void) {
  digitalWrite(13, LOW); 
  delay(100);
}

void ledBlink(void) {
  for(int i = 0; i <= 20; i++){
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    delay(50);
  }
}


//---------------------------------------------
String _strRead, _strBuf;
int _readFlg = 0;

void serialReadLineCheck(void) {
  while (Serial.available()) {
    //delay(3);  //delay to allow buffer 
    if (Serial.available() > 0) {
      char c = Serial.read();  //gets one byte from serial buffer
      if ((_readFlg == 0) && ((c == '\r') || (c == '\n'))){
        _strRead = _strBuf;
        _strBuf = "";
        _readFlg = 1;
      } 
      else if((_readFlg == 1) && ((c == '\r') || (c == '\n'))){
        //do nothing
      } 
      else {
        _strBuf += c;
      }
    }
  }
}

String serialReadLine(void) {
  String s = "";
  if (_readFlg) {
    s = _strRead; //see what was received
    _strRead = "";
    _readFlg = 0;
  }
  return s;
}





