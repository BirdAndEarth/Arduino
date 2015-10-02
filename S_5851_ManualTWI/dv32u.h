#ifndef _DV32U_H_
#define _DV32U_H_


// For Davinci 32U PinOut
#define PB0 17 //   [SS]   (RXLED)
#define PB1 15 //   [SCK]
#define PB2 16 //   [MOSI]
#define PB3 14 //   [MISO]
#define PB4  8 //   A8
#define PB5  9 // # A9
#define PB6 10 // # A10
#define PB7 11 // # 
#define PC6  5 // #
#define PC7 13 // # (LED)
#define PD0  3 // # [SCL] ExInterrupts
#define PD1  2 //   [SDA] ExInterrupts
#define PD2  0 //   [RX]
#define PD3  1 //   [TX]
#define PD4  4 //   A6
#define PD6 12 //   A11
#define PD7  6 // # A7
#define PE6  7 //   
#define PF0 23 //   A5
#define PF1 22 //   A4
#define PF4 21 //   A3
#define PF5 20 //   A2
#define PF6 19 //   A1
#define PF7 18 //   A0

#define DBG 1

#include <avr/io.h>
#include <util/delay.h>

#define I2C_SDA_PIN         1
#define I2C_SCL_PIN         0

#define I2C_SDA_PIN_BV      _BV(I2C_SDA_PIN)
#define I2C_SCL_PIN_BV      _BV(I2C_SCL_PIN)

#define _I2C_SDA_HIGH       (PORTD |= I2C_SDA_PIN_BV)
#define _I2C_SDA_LOW        (PORTD &= ~I2C_SDA_PIN_BV)

#define _I2C_SCL_HIGH       (PORTD |= I2C_SCL_PIN_BV)
#define _I2C_SCL_LOW        (PORTD &= ~I2C_SCL_PIN_BV)

void I2C_clkWait()
{
#if F_CPU == 1000000
  __asm__ __volatile__("nop");
#elif F_CPU == 1200000
  __asm__ __volatile__("nop");
#elif F_CPU == 2000000
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
#elif F_CPU == 2400000
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
  __asm__ __volatile__("nop");
#elif F_CPU == 4000000
  _delay_us(2);
#elif F_CPU == 4800000
  _delay_us(2);
#elif DBG
  _delay_us(20);
#else
  _delay_us(4);
#endif
}

void I2C_clkWait2()
{
#if F_CPU == 1000000
#elif F_CPU == 1200000
#elif F_CPU == 2000000
#elif F_CPU == 2400000
#elif F_CPU == 4000000
  _delay_us(2);
#elif F_CPU == 4800000
  _delay_us(2);
#elif DBG
  _delay_us(19);
#else
  _delay_us(3);
#endif
}

inline static void I2C_init()
{
  DDRD |= I2C_SDA_PIN_BV;
  DDRD |= I2C_SCL_PIN_BV;

  _I2C_SCL_HIGH;
  _I2C_SDA_HIGH;
}

void I2C_start()
{
  _I2C_SDA_HIGH;
  I2C_clkWait();
  _I2C_SCL_HIGH;

  I2C_clkWait();
  _I2C_SDA_LOW;
  I2C_clkWait();
  _I2C_SCL_LOW;

#if DBG
  _delay_us(100);
#endif
}

void I2C_stop()
{
  _I2C_SDA_LOW;
  I2C_clkWait();
  _I2C_SCL_HIGH;
  I2C_clkWait();
  _I2C_SDA_HIGH;
  I2C_clkWait();
#if DBG
  _delay_us(100);
#endif
}

uint8_t I2C_write(uint8_t data)
{
  uint8_t temp;
  for(temp=0x80; temp; temp>>=1)
  {
    if(data & temp)        _I2C_SDA_HIGH;
    else                _I2C_SDA_LOW;
    I2C_clkWait2();
    _I2C_SCL_HIGH;
    I2C_clkWait();
    _I2C_SCL_LOW;
  }

  DDRD &= ~I2C_SDA_PIN_BV;

  I2C_clkWait();
  temp=PINB;
  _I2C_SCL_HIGH;
  I2C_clkWait();

  _I2C_SCL_LOW;

  DDRD |= I2C_SDA_PIN_BV;

#if DBG
  _delay_us(100);
#endif

  if(temp & I2C_SDA_PIN_BV)
  {
    return 1;
  }
  return 0;
}

uint8_t I2C_read(uint8_t ACK)
{
  uint8_t data=0;
  uint8_t temp;
  uint8_t temp2;


  DDRD &= ~I2C_SDA_PIN_BV;

  for(temp=0x80; temp; temp>>=1)
  {
    I2C_clkWait();
    if(PIND & I2C_SDA_PIN_BV)        data |= temp;
    _I2C_SCL_HIGH;

    I2C_clkWait();
    _I2C_SCL_LOW;
  }

  DDRD |= I2C_SDA_PIN_BV;

  if(ACK)    _I2C_SDA_LOW;
  else    _I2C_SDA_HIGH;

  I2C_clkWait();
  _I2C_SCL_HIGH;
  I2C_clkWait();
  _I2C_SCL_LOW;

#if DBG
  _delay_us(100);
#endif

  return data;
}

#endif











