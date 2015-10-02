/**************************************
TdBlinkTest                  2015/07/24
**************************************/

int interval_ms = 500;
int led_pin = 13;


void setup() {
  pinMode(led_pin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  bli();
  delay(10000);

  bli();
  bli();
  bli();
  bli();
  bli();
  bli();
  bli();
  bli();
  bli();
  bli();
  bli();
  bli();
  bli();
  bli();
  bli();
  bli();
  bli();
  bli();
  bli();
  bli();
  delay(10000);

  on();
  delay(10000);

  off();
    delay(10000);

}

void on() {
  digitalWrite(led_pin, HIGH);
}

void off() {
  digitalWrite(led_pin, LOW);
}


void bli() {
  digitalWrite(led_pin, HIGH);
  delay(interval_ms);
  digitalWrite(led_pin, LOW);
  delay(interval_ms);
}
