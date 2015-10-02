#define MAX_BUFF 256

char buff[MAX_BUFF] = {0x00};
int counter = 0;
int cou = 1;
int flg = 0;
String st = "";

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(115200);
  Serial1.begin(115200);
  //Serial1.println("Oh! Hellow World!");
  Serial.begin(115200);

  pinMode(13, OUTPUT);

//    while (!Serial) {
//  //    //wait for serial port to connect. Needed for Leonardo only
//      }
}

void loop() {

  while (Serial1.available() > 0) {
    digitalWrite(13, HIGH);

    char data = Serial1.read();
    //Serial.print(data);

    buff[counter]  = data;
    if (data == '\n') {
      buff[counter] = '\0';
      //long long x = char2LL(buff);
      //buff[0]～buff[counter-1]までが文字列となってここでうけとれる
      //シリアル送信側で終端文字\0が最後につけられることが前提
      st = String(buff);
      //Serial.println(buff);
      Serial.println(st);
            Serial1.println(st);

      //      LL2Serial(x);

      //      Serial1.println("");

      counter = 0;
    }
    else {
      counter++;
    }
  }
  digitalWrite(13, LOW);
}




long long char2LL(char *str)
{
  long long result = 0; // Initialize result
  // Iterate through all characters of input string and update result
  for (int i = 0; str[i] != '\0'; ++i)
    result = result * 10 + str[i] - '0';
  return result;
}

void LL2Serial(long long ll)
{
  uint64_t xx = ll / 1000000000ULL;
  if (xx > 0) Serial1.print((long)xx);
  Serial1.print((long)(ll - xx * 1000000000));
}



