/*******************************************
 *******************************************/

String strRead;
int mode = 0;


void setup() {
  Serial.begin(115200);
  while(!Serial){
  }
}

void loop() {
  while (Serial.available()) {
    delay(3);  //delay to allow buffer 
    if (Serial.available() > 0) {
      char c = Serial.read();  //gets one byte from serial buffer

      if(c == '?'){
        Serial.print("TowerDetector");
      } 
      else if(c == 's') {
        mode = 1;
      } 
      else if(c == 'e') {
        mode = 0;
      }
    }
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

