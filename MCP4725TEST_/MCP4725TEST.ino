// Please refer the Microchip MCP4725 datasheet for I2C commands.

#include <Wire.h>

#define DAC_ADDRESS 0x60
#define WRITE_DAC_REGISTER 0x40
#define WRITE_DAC_REGISTER_AND_EEPROM 0x60


unsigned int adcData = 4000;
int changeStep = 2;
long da;


void setup(){
  pinMode(13, INPUT); // For use D13 LED (PC7 on DaVinci32U).
  Wire.begin();
  Serial.begin(115200);
}


void loop(){
  while (Serial.available() > 0) {
     da = Serial.parseInt();
     Serial.println(da);
      adcData = da;
      setAdc(adcData);

    
    }
  }
  //  adcData = adcData + changeStep;
  //  if (adcData <= 1500 | adcData >= 4095)
  //    changeStep = -changeStep;

void setAdc(unsigned int data) {

  byte msb = 0;
  byte lsb = 0;

  // MSB 8bit
  msb = data >> 4;

  // LSB 4bit
  lsb = (data & 0x0F) << 4 ;

  // Send data to the DAC
  Wire.beginTransmission(DAC_ADDRESS);
  Wire.write(WRITE_DAC_REGISTER_AND_EEPROM);
  Wire.write(msb);
  Wire.write(lsb);
  Wire.endTransmission();
}



