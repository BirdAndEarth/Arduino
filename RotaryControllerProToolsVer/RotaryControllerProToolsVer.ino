
/* THIS PROGRAM IS FOR DaVinci 32U */

#define PB4  8
#define PB5  9
#define PB6 10
#define PB7 11            
#define PD0  3
#define PD1  2
#define PD2  0
#define PD3  1
#define PD4  4
#define PD6 12
#define PD7 6
#define PC6 5
#define PC7  13
#define PF0 23
#define PF1 22

const char COMMAND = KEY_LEFT_GUI;
const char SHIFT = KEY_LEFT_SHIFT;
const char SPACE = 32;
const char HOME = KEY_HOME;
const char END = KEY_END;

int dRotAPin  = PD1;
int dRotBPin  = PD0;
int whitePin = PD3;
int redPin = PD2;
int bluePin = PD4;
int greenPin = PD6;
int orangePin = PB4;
int blackPin = PD7;

int ledWhitePin = PB7;
int ledBlackPin = PB6;

const int BUTTON_MAX = 6;
const int BPIN[] = {
  whitePin, redPin, bluePin, greenPin, orangePin, blackPin};

const char* BNAME[] = {
  "white", "red", "blue", "green", "orange", "black"};

const int whiteButton = 0;
const int redButton = 1;
const int blueButton = 2;
const int greenButton = 3;
const int orangeButton = 4;
const int blackButton = 5;

volatile int bState[BUTTON_MAX];
volatile int bStateOld[BUTTON_MAX];
volatile boolean bFlg[BUTTON_MAX];

volatile char m_nOldRot = 0;
volatile int m_nValue  = 0;

void setup()  
{
  // Set pinmode
  pinMode(dRotAPin, INPUT_PULLUP);
  pinMode(dRotBPin, INPUT_PULLUP);
  pinMode(whitePin, INPUT_PULLUP);
  pinMode(redPin, INPUT_PULLUP);
  pinMode(bluePin, INPUT_PULLUP);
  pinMode(greenPin, INPUT_PULLUP);
  pinMode(orangePin, INPUT_PULLUP);
  pinMode(blackPin, INPUT_PULLUP);
  pinMode(ledBlackPin, OUTPUT);
  pinMode(ledWhitePin, OUTPUT);

  // Set Interrupt
  attachInterrupt(0, rotRotEnc, CHANGE);
  Serial.begin(115200);  
}

void loop()
{
  checkButtonState();
  updateLED();
  delay(3);
}

//----------------------------------------------
// Encoder rotate to right direction
void encoderRotateRight() {
  if (bFlg[blackButton] == true) {
    //Black + White
    if (bFlg[whiteButton] == true) {
      Keyboard.begin();
      Keyboard.write(226);  
      //'\342' Keypad 2 and Down Arrow
        Keyboard.end();
    }
    // Black
    else {
      Keyboard.begin();
      Keyboard.write(KEY_DOWN_ARROW); 
      Keyboard.end();
    }
  }  
  else {
    // White
    if (bFlg[whiteButton] == true) {
      Keyboard.begin();
      Keyboard.press(SHIFT);
      Keyboard.write(KEY_RIGHT_ARROW); 
      Keyboard.release(SHIFT);        
      Keyboard.end();
    }
    // Default
    else {
      Keyboard.begin();
      Keyboard.write(KEY_RIGHT_ARROW); 
      Keyboard.end();
    }
  }
}

// Encoder rotate to left direction
void encoderRotateLeft() {

  if (bFlg[blackButton] == true) {
    //Black + White
    if (bFlg[whiteButton] == true) {
      Keyboard.begin();
      Keyboard.write(225); 
      //'\341' Keypad 1 and End
        Keyboard.end();
    } 
    // Black
    else {
      Keyboard.begin();
      Keyboard.write(KEY_UP_ARROW); 
      Keyboard.end();
    }
  }
  else {
    // White
    if (bFlg[whiteButton] == true) {
      Keyboard.begin();
      Keyboard.press(SHIFT);
      Keyboard.write(KEY_LEFT_ARROW); 
      Keyboard.release(SHIFT);        
      Keyboard.end();
    }
    // Default
    else {
      Keyboard.begin();
      Keyboard.write(KEY_LEFT_ARROW); 
      Keyboard.end();
    }
  }
}

// Button Press
void buttonPress(int button) {
  switch (button) {
  case whiteButton:
    bFlg[whiteButton] = !bFlg[whiteButton];
    break;

  case blackButton:
    bFlg[blackButton] = !bFlg[blackButton];
    break;

  case redButton:

    if (bFlg[blackButton] == true) {
      //Black + White
      if (bFlg[whiteButton] == true) {
        Keyboard.begin();
        Keyboard.write(227);   
        //'\343' Keypad 3 and PageDn
          Keyboard.end();
      }
      // Black
      else {
        Keyboard.begin();
        Keyboard.press(COMMAND);
        Keyboard.write(98); // b
        Keyboard.release(COMMAND);
        Keyboard.end();
      }
    }  
    else {
      Keyboard.begin();
      Keyboard.press(COMMAND);
      Keyboard.write(98); // b
      Keyboard.release(COMMAND);
      Keyboard.end();
    }
          break;


  case blueButton:

    if (bFlg[blackButton] == true) {
      //Black + White
      if (bFlg[whiteButton] == true) {
        Keyboard.begin();
        Keyboard.write(SPACE);   
        Keyboard.end();
 
      }
      // Black
      else {
        Keyboard.begin();
        Keyboard.press(COMMAND);
        Keyboard.write(122); // z
        Keyboard.release(COMMAND);
        Keyboard.end();
      }
    }  
    else {
      Keyboard.begin();
      Keyboard.press(COMMAND);
      Keyboard.write(122); // z
      Keyboard.release(COMMAND);
      Keyboard.end();
    }

     break;

  case greenButton:
    Keyboard.begin();
    Keyboard.write(SPACE); 
    Keyboard.end();
    break;

  case orangeButton:
    break;

  default: 
    break;
  }
}

// Button Release
void buttonRelease(int button) {
  switch (button) {
  case whiteButton:
    break;

  case blackButton:
    break;

  case redButton:
    break;

  case blueButton:
    break;

  case greenButton:
    break;

  case orangeButton:
    break;

  default: 
    break;
  }
}




// ---------------------------------------------------
// Check state of buttons
void checkButtonState(void) {

  for (int i = 0; i < BUTTON_MAX; i++) {
    bState[i] = digitalRead(BPIN[i]);

    // Detect Button Press
    if (bState[i] == 1 && bStateOld[i] == 0) {
      buttonPress(i);
    } 
    // Detect Button Release
    else if (bState[i] == 0 && bStateOld[i] == 1) {
      buttonRelease(i);
    } 
    // No change
    else {
    }

    bStateOld[i] = bState[i];
  }
}

// Update LED
void updateLED(void){
  digitalWrite(ledWhitePin, bFlg[whiteButton]);
  digitalWrite(ledBlackPin, bFlg[blackButton]);
}


// 外部割り込みから呼び出される変数
void rotRotEnc(void)
{
  if(!digitalRead(dRotAPin)) {  // ロータリーエンコーダー回転開始
    if(digitalRead(dRotBPin)) {
      //右回転かな?
      m_nOldRot = 'R';
    } 
    else {
      //左回転かな?
      m_nOldRot = 'L';
    }
  } 
  else {  // ロータリーエンコーダー回転停止
    if(digitalRead(dRotBPin)) {
      if(m_nOldRot == 'L') { 
        encoderRotateLeft();
      }
    }
    else {
      if(m_nOldRot == 'R'){
        encoderRotateRight();
      }
    }

    // ここでロータリーエンコーダーの状態をクリア
    m_nOldRot = 0;
  }
}



