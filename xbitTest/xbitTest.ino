


int CLK = 2;
int DIN = 3;
int CS  = 4;
int in = 0;

void setup(){
  pinMode(CLK, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
}



void loop(){

  digitalWrite(CS, LOW);
  delay(1);

  for (int i = 15; i >= 0; i--){
    digitalWrite(DIN, (in>>i) & 1);
    digitalWrite(CLK, HIGH);
    digitalWrite(DIN, LOW);
    digitalWrite(CLK, LOW);
  }

  digitalWrite(CS, HIGH);

  in++;

  delay(1);
}







