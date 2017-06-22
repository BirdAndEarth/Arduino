void setup() {
  // put your setup code here, to run once:


pinMode(32, INPUT);
pinMode(33, OUTPUT);

}

void loop() {
digitalWrite(33, digitalRead(32));





}
