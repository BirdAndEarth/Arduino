void setup() {
  // put your setup code here, to run once:

  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);

}

void loop() {
  static boolean flg = false;
  
  flg = !flg;
  
  digitalWrite(18, flg);
  digitalWrite(19, flg);
  digitalWrite(20, flg);
  digitalWrite(21, flg);

  delay(100);
  
}
