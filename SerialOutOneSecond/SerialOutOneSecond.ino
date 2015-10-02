
const int LedPin = 13;  // Analog input pin that the potentiometer is attached to

void setup() {
  Serial.begin(115200);
  pinMode(LedPin, OUTPUT);
  digitalWrite(LedPin, LOW);
}

void loop() {
  
  digitalWrite(LedPin, HIGH);
  Serial.print("Hello world! I'm DaVinci32U!");      
  Serial.println("");   
  digitalWrite(LedPin, HIGH);

  delay(1000);                     
}
