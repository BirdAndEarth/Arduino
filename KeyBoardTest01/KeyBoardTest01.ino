
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
#define PD7 16

#define PC6 13
#define PC7  5

#define PE6 7

// ロータリーエンコーダーの配線に合わせる
int dRotAPin  = PD1;
int dRotBPin  = PD0;

// ロータリーエンコーダーの状態を記憶する
// 割り込み中に変化する変数はvolatileはをつけて宣言する
volatile char m_nOldRot = 0;

// 今回はLCDに回転回数を表示させる
volatile int m_nValue  = 0;

void setup()  
{
  // LCDのセットアップ
  // 16文字×2行のLCDを使用します
  
  // ピンの設定
  // INPUTモードにします。
  pinMode(dRotAPin, INPUT);
  pinMode(dRotBPin, INPUT);
  
  // プルアップを有効にします
  digitalWrite(dRotAPin, HIGH);
  digitalWrite(dRotBPin, HIGH);
  
//  Serial.begin(115200);
  // 外部割り込みを設定します
  // D2ピンが 変化 した時にrotRotEnd()を呼び出します
  attachInterrupt(0, rotRotEnc, CHANGE);
}

void loop()
{





}

// 外部割り込みから呼び出される変数
void rotRotEnc(void)
{
  if(!digitalRead(dRotAPin)){  // ロータリーエンコーダー回転開始
    if(digitalRead(dRotBPin)){
      //右回転かな?
      m_nOldRot = 'R';
    } else {
      //左回転かな?
      m_nOldRot = 'L';
    }
  } else {  // ロータリーエンコーダー回転停止
    if(digitalRead(dRotBPin)){
      if(m_nOldRot == 'L'){ 
        // 左回転の時の処理
        m_nValue--;
          Keyboard.begin();
       Keyboard.write(KEY_LEFT_ARROW); 
Keyboard.end();
      }
    } else {
      if(m_nOldRot == 'R'){
        //右回転の時の処理
        m_nValue++;
  Keyboard.begin();
       Keyboard.write(KEY_RIGHT_ARROW); 
  Keyboard.end();

      }
    }
    // ここでロータリーエンコーダーの状態をクリア
   
//Serial.println(m_nValue);
    m_nOldRot = 0;
  }
}
