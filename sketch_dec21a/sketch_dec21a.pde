 //example soner

/*
for EZ1
 ---------------
|O              |
|   (SENSOR)    |
|              O|
| o o o o o o o |
 ---------------
  B P A R T + G                       
  W W N X X 5 N            
              D
    TOP VIEW


VCC -> +5V
GND -> GND
AN  -> Analog 0
*/





int sencerPin = 0;

void setup(){
  Serial.begin(115200);
  
  
}

void loop() {
  int value = analogRead(sencerPin);
  
  int rangeInInches = value / 2;
  int rangeInCentimeters = round((float)rangeInInches * 2.54);
 
/*   
  Serial.print(rangeInInches);
  Serial.print(" inches   ");
  Serial.print(rangeInCentimeters);
  Serial.print(" cm    ");
  Serial.print(value);
  Serial.println("/1024 analog   ");
*/
  int i;
  for(i = 0; i < rangeInCentimeters/10; i++)
    Serial.print("|");

  Serial.print(" ");
  Serial.print(rangeInCentimeters);
  Serial.println(" cm    ");

  delay(25);
  
}

