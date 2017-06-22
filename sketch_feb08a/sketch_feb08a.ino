#define MAX 20


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  String stringOne = "Hello String";                // 文字列定数を使用
  byte buf[MAX];


  //Serial.println(stringOne.charAt(1));  // bと表示されます
  stringOne.getBytes(buf, MAX);

  for (int i = 0; i < MAX; i++) {
    Serial.print(i);
    Serial.print('\t');
    Serial.print(stringOne.charAt(i));
    Serial.print('\t');
    Serial.print(buf[i], DEC);
        
        Serial.print('\n');

  }
  Serial.print('\n');
  delay(5000);
}
