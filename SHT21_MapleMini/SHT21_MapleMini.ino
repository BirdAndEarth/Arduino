#include <Wire.h>

#define ADDR 0b1000000
#define CMD_T 0b11100011
#define CMD_RH 0b11100101

void setup() {
  Wire.begin();
  Serial.begin(115200);
  pinMode(33, OUTPUT);
}


void loop() {
  uint8_t msb, lsb, chk; // 読み出す3byte
  uint16_t st;           // 計測した生データ
  float t;               // 摂氏として計算した温度
  float h;

  digitalWrite(33, HIGH);




  /* onndo */
  // コマンドの送信
  Wire.beginTransmission(ADDR);
  Wire.write(CMD_T);
  Wire.endTransmission();

  // 結果の3バイトを読み込む
  Wire.requestFrom(ADDR, 3);
  while (!Wire.available()) {}
  msb = Wire.read();
  lsb = Wire.read();
  chk = Wire.read();

  // 計測結果の生データ
  st = msb << 8 | lsb;

  // 摂氏の温度の計算
  t = -46.85 + 175.72 * (float)st / (16.0 * 16.0 * 16.0 * 16.0);



  /* shitudo */
  // コマンドの送信
  Wire.beginTransmission(ADDR);
  Wire.write(CMD_RH);
  Wire.endTransmission();

  // 結果の3バイトを読み込む
  Wire.requestFrom(ADDR, 3);
  while (!Wire.available()) {}
  msb = Wire.read();
  lsb = Wire.read();
  chk = Wire.read();

  // 計測結果の生データ
  st = msb << 8 | lsb;

  // 摂氏の温度の計算
  h = -6.0 + 125.0 / 65536.0 * (float)st;

  digitalWrite(33, LOW);


  // シリアルポートに書き込む
  Serial.print("Temp:");
  Serial.println(t);

  delay(5000);
  Serial.print("Humi:");
  Serial.println(h);

  // 3秒休憩
  delay(5000);
}
