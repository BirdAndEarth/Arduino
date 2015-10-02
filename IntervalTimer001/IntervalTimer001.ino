#include <AlphaRemote.h>

#define IRPIN 2
#define BTN1 9
#define BTN2 6
#define GND1 7
#define GND2 4
#define BTNEX 10
#define LED 13

const int BUTTON_MAX = 3;
const int PRESS_TIME = 1000; // ms
int button1  = 0;
int button2  = 1;
int buttonEx = 2;

String buttonName[] = {
  "button1", "button2", "buttonEx"
};

int buttonPin[] = {
  BTN1, BTN2, BTNEX
};

unsigned long TimeNow[3];

//boolean RecFlg = false;
//boolean IntervalTimerFlg = false;
int intervalTime = 0;
int mode = 0; // Ready 0, set 1, 
boolean setMode4Flg = false;
int intervalCount = 0;
boolean button1PressFlg = 0;
boolean button2PressFlg = 0;
boolean buttonExPressFlg = 0;


void setup()
{
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(GND1, OUTPUT);
  pinMode(GND2, OUTPUT);
  pinMode(BTNEX, INPUT_PULLUP);
  pinMode(IRPIN, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(GND1, LOW);
  digitalWrite(GND2, LOW);
  digitalWrite(IRPIN, LOW);

  Serial.begin(115200);
  AlphaRemote.begin(IRPIN);

}

void loop()
{
  checkButtonState();
}

void readyMode()
{

}

void intervalTimer()
{
  unsigned long t = 0;
  unsigned long tOld = 0;
  digitalWrite(LED, HIGH);

  while (1){
    checkButtonState(); 
    if (mode != 3){
      break;
    }
    t = millis();
    if (t - tOld > intervalTime){
      AlphaRemote.shutter();
      tOld = t;
    }
  }
  digitalWrite(LED, LOW);
}





void setMode(int n)
{
  Serial.println(n);
  mode = n;
  ledBlink(n);
}

void ledBlink(int n) {
  for (int i = 0; i < n + 1; i++){  
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
  }
}

void ledBlink2(int ten, int five, int one) {
  for (int i = 1; i < ten + 1; i++){  
    digitalWrite(LED, HIGH);
    delay(700);
    digitalWrite(LED, LOW);
    delay(200);
    Serial.println("10");
  }
  
  for (int i = 1; i < five + 1; i++){  
    digitalWrite(LED, HIGH);
    delay(300);
    digitalWrite(LED, LOW);
    delay(200);
    Serial.println("5");
  }
  
  for (int i = 1; i < one + 1; i++){  
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(200);
    Serial.println("1");

  }
}


void intervalTimeCheck() {
  int ten = 0;
  int five = 0;
  int one = 0;
  int temp = 0;
  
  Serial.print("intervalCount = ");
  Serial.println(intervalCount);
  
  ten = intervalCount / 10;
  temp = intervalCount % 10;
  five = temp / 5;
  one = temp % 5;
    
  Serial.print("10 * ");
  Serial.print(ten);
  Serial.print("\t5 * ");
  Serial.print(five);
  Serial.print("\t1 * ");
  Serial.println(one);
  
  ledBlink2(ten, five, one);
  
}




// button 1
void button1Press()
{
  button1PressFlg = true;

  //  Serial.println("button1 Press.");

  switch (mode) {
  case 0:  //Shutter
    if (!button2PressFlg){
      digitalWrite(LED, HIGH);
      AlphaRemote.shutter();
      digitalWrite(LED, LOW);
    }
    break;
  case 1:  //Rec
    digitalWrite(LED, HIGH);
    AlphaRemote.rec();
    digitalWrite(LED, LOW);

    break;
  case 2:  //Interval Ready
    if (!button2PressFlg){
      mode = 3; //Interval Start
      intervalTimer();
    }
    else {
      setMode4Flg = true;
      setMode(4);
      intervalCount = 0;
    }
    break;
  case 3:  
    mode = 2; // Interval stop
    break;
  case 4:  //Interval Setting
    intervalCount++;
    break;
  }
}

void button1Release()
{
  button1PressFlg = false;
  //  Serial.println("button1 Release.");

}
void button1LongPress()
{
  //  Serial.println("button1 LongPress.");

}

// button 2
void button2Press()
{
  button2PressFlg = true;
}

void button2Release()
{
  button2PressFlg = false;
  switch (mode) {
  case 0:  // Shutter
    setMode(1);        
    break;
  case 1:  // Rec
    setMode(2);        
    break;
  case 2:  // Interval Ready
    setMode(0);    
    break;
  case 3:  // Interval Timer

    break;
  case 4:  // Interval Setting
    if (!setMode4Flg) {
      if (intervalCount > 1){
        intervalTime = intervalCount * 1000;
      }
      else {
        intervalTime = 1000;
      }        
      mode = 2;
      intervalTimeCheck();
      Serial.print("intervalTimer = ");
      Serial.println(intervalTime);
    }
    else {
      setMode4Flg = false;
    }
    break;
  }
}

void button2LongPress()
{
  //  Serial.println("button2 LongPress.");
}

// button Ex
void buttonExPress()
{
  buttonExPressFlg = true;

}

void buttonExRelease()
{
  buttonExPressFlg = false;

}

void buttonExLongPress()
{
}


// APIs ----------------------------------------------------------------
// check the button state.
int checkButtonState()
{
  static unsigned long checkTime = 0;
  static unsigned long checkTimeOld = 0;

  checkTime = millis();
  if (checkTimeOld - checkTime <= 3){
    return 0;
  }
  checkTimeOld = checkTime;

  static int buttonState[BUTTON_MAX];
  static boolean buttonFlg[] = {
    false, false, false
  };

  static boolean buttonFlgOld[] = {
    false, false, false
  };

  static unsigned long buttonPressingTime[BUTTON_MAX];
  static unsigned long buttonPressedTime[BUTTON_MAX];
  int flg = 0;

  // Check all buttons.
  for (int i = 0; i < BUTTON_MAX; i++) {

    // Init.
    buttonState[i] = 0;

    // Read button state.
    buttonFlg[i] = !digitalRead(buttonPin[i]);

    // Check for Press.
    if (buttonFlgOld[i] == LOW && buttonFlg[i] == HIGH) {
      buttonPressedTime[i] = millis();
      buttonState[i] = 1;
      flg = 10 * i + 1;
    }
    // Check for Release.
    else if (buttonFlgOld[i] == HIGH && buttonFlg[i] == LOW) {
      buttonPressedTime[i] = 0;
      buttonState[i] = 2;
      flg = 10 * i + 2;
    }
    // Check for Long Press.
    else if (buttonFlgOld[i] == HIGH && buttonFlg[i] == HIGH) {
      if ((buttonPressedTime[i] > 0) && (millis() - buttonPressedTime[i] > PRESS_TIME)) {
        buttonPressedTime[i] = 0;
        buttonState[i] = 3;
        flg = 10 * i + 3;
      }
    }

    // Init.
    buttonFlgOld[i] = buttonFlg[i];
  }

  // Call ivent handlers.  
  for (int i = 0; i < BUTTON_MAX; i++) {
    switch (buttonState[i]) {
    case 1:
      _buttonPress(i);
      break;
    case 2:
      _buttonRelease(i);    
      break;
    case 3:
      _buttonLongPress(i);    
      break;
    }
  }
  return flg;
}

void _buttonPress(int buttonNo){
  switch (buttonNo){
  case 0:
    button1Press();    
    break;
  case 1:
    button2Press();    
    break;
  case 2:
    buttonExPress();    
    break;   
  }
}
void _buttonRelease(int buttonNo){
  switch (buttonNo){
  case 0:
    button1Release();    
    break;
  case 1:
    button2Release();    
    break;
  case 2:
    buttonExRelease();    
    break;   
  }
}
void _buttonLongPress(int buttonNo){
  switch (buttonNo){
  case 0:
    button1LongPress();
    break;
  case 1:
    button2LongPress();
    break;
  case 2:
    buttonExLongPress();
    break;   
  }
}





















