




void setup() {




  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
//  pinMode(A1, INPUT);
  digitalWrite(A0, HIGH);
  digitalWrite(A2, LOW);

  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(A1);
  int outputValue= map(sensorValue, 5, 1010, 0, 255);
  
  if (outputValue > 255) outputValue = 255;
  if (outputValue < 0) outputValue = 0;
  
  analogWrite(3, outputValue);
  Serial.print(sensorValue);
  Serial.print("\t");
  Serial.println(outputValue);
  delay(100);




}
