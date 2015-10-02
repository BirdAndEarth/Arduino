void setup() {
  Serial.begin(115200) ;
  Serial1.begin(2400);
}

void loop() {
  int n, i, ch ;
  
  n = Serial1.available() ;
  if (n > 0) {
        i = n ;
    while (i--) {
      ch = Serial1.read() ;
      Serial.print((char)ch) ;
    }
  }
  delay(1000) ;
}
