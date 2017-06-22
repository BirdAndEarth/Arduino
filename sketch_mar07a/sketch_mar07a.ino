void setup() {
  // put your setup code here, to run once:
pinMode(10,OUTPUT);
}

void loop() {
  digitalWrite(10,HIGH);
  delayMicroseconds(10);
  digitalWrite(10,LOW);
  delay(100);
}
