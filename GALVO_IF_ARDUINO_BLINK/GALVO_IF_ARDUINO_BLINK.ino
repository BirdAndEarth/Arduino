/*
  Checker for the Arduino Section 
  of 20.201.B GALVO I/F BOARD

*/

int led4 = 9;
int led5 = 8;

void setup() {
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}

void loop() {
  digitalWrite(led4, HIGH);
  delay(100);
  digitalWrite(led4, LOW);
  
  digitalWrite(led5, HIGH);
  delay(500);
  digitalWrite(led5, LOW);
  

}
