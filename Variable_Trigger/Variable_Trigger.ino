#define OUTP 30 // Output Trigger
#define BUT  32 // Start Switch
#define LEDP 33 // Indicate LED
#define GNDP 26 // BTN GRD
#define BTNP 33 // BUTTON PIN


#define POT_GND_PIN  5 // 
#define POT_VCC_PIN  3 // 
#define POT_VALUE_PIN  4// 


unsigned long rates = 1000;  // Hz  Q-Rate
int width = 1;  // Pulse Width
int output_sec = 10; // Output seconds

/*
 * スタートスイッチを押すと、指定Qレートで
 * output_sec秒間トリガを出力する。
 */

unsigned long ctr;

void setup() {
  // put your setup code here, to run once:

  pinMode(OUTP, OUTPUT);
  pinMode(BUT, INPUT);
  pinMode(33, OUTPUT);
  pinMode(GNDP, OUTPUT);
  pinMode(BTNP, INPUT);
  pinMode(POT_VCC_PIN, OUTPUT);
  pinMode(POT_GND_PIN, OUTPUT);
  digitalWrite(GNDP, LOW);

  digitalWrite(POT_GND_PIN, LOW);
  digitalWrite(POT_VCC_PIN, HIGH);

  Serial.begin(115200);


  ctr = 1000000 / (1000000 / rates) * (unsigned long)output_sec;
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long st_time;
  unsigned long cycles = 0;
  static int sens = 0;
  int val = 0;
  sens = analogRead(POT_VALUE_PIN);
  val = (map(sens, 30, 4060, 0, 20));
  if (val == 0) {
    val = 1;
  }



  if (digitalRead(BUT) == HIGH)
  {

    st_time = micros();
    while (cycles < ctr)
    {
      digitalWrite(33, HIGH);
      if ((micros() - st_time) > (cycles * (1000000 / rates)))
      {
        digitalWrite(OUTP, HIGH);
        //        delayMicroseconds(val);
        de(val);
        digitalWrite(OUTP, LOW);
        cycles++;
      }

      sens = analogRead(POT_VALUE_PIN);
      val = (map(sens, 30, 4060, 0, 20));
      if (val == 0) {
        val = 1;
      }


    }
    cycles = 0;
digitalWrite(33, LOW);
  }
  
}

void de(int val) {
  for (int i = 0; i < val; i++) {
    __asm__("nop\n\t");
  }
}


