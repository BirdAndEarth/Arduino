#include <SPI.h>

SPIClass SPI_2(2);
int latchPin = 31;


void setup() {
  pinMode(latchPin, OUTPUT);
  SPI_2.begin();
  SPI_2.setBitOrder(MSBFIRST);
  SPI_2.setClockDivider(SPI_CLOCK_DIV16);
  SPI_2.setDataMode(SPI_MODE0);
  digitalWrite(latchPin, LOW);

}

void loop() {
  unsigned long data32;
  byte data1;
  byte data2;
  byte data3;

  for (int i = 0; i < 18; i++) {
    data32 = (1 << i);
  
  
  data1 = data32 >> 16;
  data2 = data32 >> 8;
  data3 = data32;

  digitalWrite(latchPin, 0);
  
  SPI_2.transfer(data1);
  SPI_2.transfer(data2);
  SPI_2.transfer(data3);

  digitalWrite(latchPin, 1);
  delay(30);
  }
}

