
#define OUTP 30 // Output Trigger
#define BUT  32 // Start Switch
#define LEDP 33 // Indicate LED
#define GNDP 26 // BTN GRD
#define BTNP 33 // BUTTON PIN

unsigned long rates = 1000;  // Hz  Q-Rate
int width = 1;  // Pulse Width
int output_sec = 1; // Output seconds

/*
 * スタートスイッチを押すと、指定Qレートで
 * output_sec秒間トリガを出力する。
 */

unsigned long ctr;

void setup() {
  // put your setup code here, to run once:

  pinMode(OUTP, OUTPUT);
  pinMode(BUT, INPUT);
  pinMode(LEDP,OUTPUT);
  pinMode(GNDP, OUTPUT);
  pinMode(BTNP, INPUT);

  digitalWrite(GNDP, LOW);
  

  ctr = 1000000 / (1000000 / rates) * (unsigned long)output_sec;
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long st_time;
  unsigned long cycles = 0;
  
  if(digitalRead(BUT) == HIGH)
  {
    st_time = micros();
    while(cycles < ctr)
    {
      if((micros() - st_time) > (cycles * (1000000 / rates)))
      {
        digitalWrite(OUTP, LOW);
        //delayMicroseconds(width);
        digitalWrite(OUTP, HIGH);
        cycles++;
      }
    }
    cycles = 0;
  }
}
