int outPin = 13;

void setup() {
  pinMode(outPin, OUTPUT);
  digitalWrite(outPin, HIGH);
}

void loop() {
  digitalWrite(outPin, HIGH);
  digitalWrite(outPin, LOW);
  delay(5);

}
