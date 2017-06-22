//=================================================
// Multiple Serial For Maple Mini2
//                 Rev. 1 16/01/21 shiu
//
//=================================================

/*
    UART1 <-THRU-> UART2
    UART3 is Monitor out
*/

void setup() {

  Serial.begin(1200);
  Serial1.begin(1200);
  Serial2.begin(1200);
  Serial3.begin(1200);
}

void loop() {
  com1_check();
  com2_check();
}

// ===============================================================
/* *****************************
    Serial1 THRU to Serial2
 * ***************************** */
int com1_check() {

  // Serial Read
  while (Serial1.available()) {
    int incoming = Serial1.read();

    // send thru to Serial2
    Serial2.write(incoming);
    Serial.write(incoming);
    Serial3.write(incoming);

  }
}
/* *****************************
    Serial2 THRU to Serial1
 * ***************************** */
int com2_check() {

  // Serial Read
  while (Serial2.available()) {
    int incoming = Serial2.read();

    // send thru to Serial1
    Serial1.write(incoming);
    Serial.write(incoming);
    Serial3.write(incoming);
  }
}






