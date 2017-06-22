#include "font5x7.h"

/*
 *
 *
 *
 *
 *
 *
 *
 */


String PVER = "0001";
String PDATE = "16/04/11";

/*-- PIN CONFIGURE -----------------------------------*/
// OLED
#define OLED_PIN_PW   22
#define OLED_PIN_D7   21
#define OLED_PIN_D6   20
#define OLED_PIN_D5   19
#define OLED_PIN_D4   18
#define OLED_PIN_EN   17
#define OLED_PIN_RW   16
#define OLED_PIN_RS   15

#define PI_PWR_PIN    3
#define PI_O01_PIN    4
#define PI_O02_PIN    5
#define PI_O03_PIN    6
#define PI_O04_PIN    7
#define PI_I01_PIN    10
#define PI_I02_PIN    11
#define PI_I03_PIN    12
#define PI_I04_PIN    13

#define SW_PWR_PIN    30
#define SW_FUNC_PIN   31

#define LED_PIN       33

#define SETTLE_DELAY_MS  10
#define SHUTDOWN_DELAY_MS 12000

/*-- Constants -----------------------------------*/
// OLED
#define WIDTH    100
#define HEIGHT    16
#define GRAPHIC  200

int bmp[HEIGHT][WIDTH] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
int bmp2[HEIGHT][WIDTH] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

byte graphic[GRAPHIC];

/* Serials */
String strSeriaIncoming = "";         // a string to hold incoming data
String strSeriaIncoming1 = "";         // a string to hold incoming data
String strSeriaIncoming2 = "";         // a string to hold incoming data
String strSeriaIncoming3 = "";         // a string to hold incoming data

boolean blnStringComplete = false;  // whether the string is complete
boolean blnStringComplete1 = false;  // whether the string is complete
boolean blnStringComplete2 = false;  // whether the string is complete
boolean blnStringComplete3 = false;  // whether the string is complete


/*******************************************************************
 OLED
 *******************************************************************/
void write4bits(uint8_t value) {
  digitalWrite(OLED_PIN_D7, (value >> 3) & 0x01);
  digitalWrite(OLED_PIN_D6, (value >> 2) & 0x01);
  digitalWrite(OLED_PIN_D5, (value >> 1) & 0x01);
  digitalWrite(OLED_PIN_D4, value & 0x01);
  pulseEnable();
}

void write4bits_init(uint8_t value) {
  digitalWrite(OLED_PIN_D7, (value >> 3) & 0x01);
  digitalWrite(OLED_PIN_D6, (value >> 2) & 0x01);
  digitalWrite(OLED_PIN_D5, (value >> 1) & 0x01);
  digitalWrite(OLED_PIN_D4, value & 0x01);
  pulseEnable_init();
}

void send(uint8_t value, uint8_t modeRS , uint8_t modeRW) {
  digitalWrite(OLED_PIN_RS, modeRS);
  digitalWrite(OLED_PIN_RW, modeRW);
  write4bits(value >> 4);
  write4bits(value);
}

void command(uint8_t value) {
  busy();
  send(value, LOW, LOW);
}

void data_write(uint8_t value) {
  busy();
  send(value, HIGH, LOW);
}

void pulseEnable() {
  digitalWrite(OLED_PIN_EN, LOW);
  delayMicroseconds(1);
  digitalWrite(OLED_PIN_EN, HIGH);
  delayMicroseconds(1);
  digitalWrite(OLED_PIN_EN, LOW);
}

void pulseEnable_init() {
  digitalWrite(OLED_PIN_EN, LOW);
  delay(1);
  digitalWrite(OLED_PIN_EN, HIGH);
  delay(1);
  digitalWrite(OLED_PIN_EN, LOW);
  delay(1);
}

void pinModeAll(WiringPinMode value) {
  pinMode(OLED_PIN_PW, value);
  pinMode(OLED_PIN_RS, value);
  pinMode(OLED_PIN_RW, value);
  pinMode(OLED_PIN_EN, value);
  pinMode(OLED_PIN_D4, value);
  pinMode(OLED_PIN_D5, value);
  pinMode(OLED_PIN_D6, value);
  pinMode(OLED_PIN_D7, value);

  digitalWrite(OLED_PIN_PW, LOW);
  delay(500);
  digitalWrite(OLED_PIN_PW, HIGH);
  delay(500);
}

void busy() {
  pinMode(OLED_PIN_D7, INPUT);
  int busy = HIGH;
  while (busy) {
    digitalWrite(OLED_PIN_RS, LOW);
    digitalWrite(OLED_PIN_RW, HIGH);
    pulseEnable();
    busy = digitalRead(OLED_PIN_D7);
    pulseEnable();
  }
  pinMode(OLED_PIN_D7, OUTPUT);
}

void sync() {
  busy();
  digitalWrite(OLED_PIN_RS, LOW);
  digitalWrite(OLED_PIN_RW, LOW);
  write4bits_init(0x0);
  write4bits_init(0x0);
  write4bits_init(0x0);
  write4bits_init(0x0);
  write4bits_init(0x0);
}

void functionSet() {
  busy();
  digitalWrite(OLED_PIN_RS, LOW);
  digitalWrite(OLED_PIN_RW, LOW);
  write4bits(0x2);
  command(0x28);//Function Set[0 0 1 DL N F FT1 FT0]//
}

void displayOn() {
  command(0x0c);//Display ON/OFF Control [0 0 0 0 1 D C B]
}

void displayClear() {
  command(0x01);
}

void returnHome() {
  command(0x02);
}

void entryModeSet() {
  command(0x06); // Entry Mode Set [0 0 0 0 0 0 0 1 I/D S]
}

void graphicModeSet() {
  command(0x1f); // Cursor / Display Shift / Mode / Pwr[ 0 0 0 1 G/C PWR 1 1]
}

void OLED_init() {

  sync();
  functionSet();
  displayOn();
  entryModeSet();
  graphicModeSet();
  displayClear();
  returnHome();


}

void OLED_setup() {
  pinModeAll(OUTPUT);
  sync();
  functionSet();
  displayOn();
  entryModeSet();
  graphicModeSet();
  displayClear();
  returnHome();
}

void OLED_Cursor(int col, int row) {
  command((0x80 | col));
  command((0x40 | row));
}

void graphic_input(int col, byte *p) {
  for (int i = 1; i < 20; i = i + 2) {
    graphic[i + col] |= p[i];
  }
  for (int i = 0; i < 20; i = i + 2) {
    graphic[i + col] |= p[i];
  }
}

void OLED_display(byte *p) {
  returnHome();
  updateBmp();
  for (int i = 1; i < 200; i = i + 2) {
    data_write(p[i]);
  }
  for (int i = 0; i < 200; i = i + 2) {
    data_write(p[i]);
  }
}

void graphic_clear() {
  for (int i = 0; i < GRAPHIC; i++ )
  {
    graphic[i] = 0x00; //グラフィック変数のクリア
  }
}

void updateBmp() {
  byte b1 = 0x00;
  byte b2 = 0x00;
  for (int w = 0; w < WIDTH; w++) {
    b1 = 0x00;
    b2 = 0x00;
    for (int h = 0; h <= 7; h++) {
      if (bmp[h][w] == 1) {
        b1 |= 0x01 << h;
      }
    }
    graphic[(int)(w * 2 + 1) ] = b1;
    for (int h = 0; h <= 7; h++) {
      if (bmp[h + 8][w] == 1) {
        b2 |= 0x01 << h;
      }
    }
    graphic[(int)(w * 2) ] = b2;
  }
}

void clearBmp() {
  for (int w = 0; w < WIDTH; w++) {
    for (int h = 0; h < HEIGHT; h++) {
      bmp[h][w] = 0;
    }
  }
}

void OLD_print5x7(String S, int x, int y) {
  int fontWidth = 6;
  int fontHeight = 8;
  int c = 0;
  int count = 0;

  for (int i = 0 ; i < S.length(); i++) {
    c = S.charAt(i);
    _add5x7Char2Bmp(c, x + (int)(i * fontWidth), y);
  }
}

void _add5x7Char2Bmp(int c, int x, int y) {
  int fontWidth = 6;
  int fontHeight = 8;

  for (int w = 0; w < fontWidth ; w++) {
    for (int h = 0; h < fontHeight ; h++) {
      if ((h + y < HEIGHT) && (w + x < WIDTH)) {
        bmp[h + y][w + x] = (byte)((font5x7[c * fontWidth + w] >> h)  & 0x01);
      }
    }
  }
}


/*******************************************************************
 PINS
 *******************************************************************/
void pinInit() {
  pinMode(PI_PWR_PIN, OUTPUT);
  pinMode(PI_O01_PIN, INPUT_PULLDOWN);
  pinMode(PI_O02_PIN, INPUT_PULLDOWN);
  pinMode(PI_O03_PIN, INPUT_PULLDOWN);
  pinMode(PI_O04_PIN, INPUT_PULLDOWN);
  pinMode(PI_I01_PIN, OUTPUT);
  pinMode(PI_I02_PIN, OUTPUT);
  pinMode(PI_I03_PIN, OUTPUT);
  pinMode(PI_I04_PIN, OUTPUT);
  pinMode(SW_PWR_PIN, INPUT_PULLDOWN);
  pinMode(SW_FUNC_PIN, INPUT_PULLDOWN);
  pinMode(LED_PIN, OUTPUT);
}

void polling() {
  static int swPwrStateOld = 0;
  static int swFuncStateOld = 0;
  static int piO1StateOld = 0;
  static int piO2StateOld = 0;
  static int piO3StateOld = 0;
  static int piO4StateOld = 0;

  int swPwrState = digitalRead(SW_PWR_PIN);
  int swFuncState = digitalRead(SW_FUNC_PIN);
  int piO1State = digitalRead(PI_O01_PIN);
  int piO2State = digitalRead(PI_O02_PIN);
  int piO3State = digitalRead(PI_O03_PIN);
  int piO4State = digitalRead(PI_O04_PIN);

  if (swPwrState && !swPwrStateOld) {
    delay(SETTLE_DELAY_MS);
    if (digitalRead(SW_PWR_PIN)) {
      swPowerRising();
    }
  }
  if (!swPwrState && swPwrStateOld) {
    delay(SETTLE_DELAY_MS);
    if (digitalRead(SW_PWR_PIN) == LOW) {
      swPowerFalling();
    }
  }
  if (swFuncState && !swFuncStateOld) {
    delay(SETTLE_DELAY_MS);
    if (digitalRead(SW_FUNC_PIN) == HIGH) {
      swFuncRising();
    }
  }
  if (!swFuncState && swFuncStateOld) {
    delay(SETTLE_DELAY_MS);
    if (digitalRead(SW_FUNC_PIN) == LOW) {
      swFuncFalling();
    }
  }
  if (piO1State && !piO1StateOld) {
    delay(SETTLE_DELAY_MS);
    if (digitalRead(PI_O01_PIN) == HIGH) {
      piO1Rising();
    }
  }
  if (!piO1State && piO1StateOld) {
    delay(SETTLE_DELAY_MS);
    if (digitalRead(PI_O01_PIN) == LOW) {
      piO1Falling();
    }
  }

  swPwrStateOld = swPwrState;
  swFuncStateOld = swFuncState;
  piO1StateOld = piO1State;
  piO2StateOld = piO2State;
  piO3StateOld = piO3State;
  piO4StateOld = piO4State;
}

void swPowerRising() {
  dbg("swPowerRising()");
  digitalWrite(PI_PWR_PIN, HIGH);
  OLED_setup();

  //  String S = "OC1 " + PVER;
  //  clearBmp();
  //  OLD_print5x7(S, 0, 5);
  //logo();
  OLED_display(graphic);
}

void logo() {
  for (int w = 0; w < WIDTH; w++) {
    for (int h = 0; h < HEIGHT; h++) {
      bmp[h][w] = bmp2[h][w];
    }
  }
}


void swPowerFalling() {
  dbg("swPowerFalling()");
  piShutDown();
  //  digitalWrite(PI_PWR_PIN, LOW);

}

void swFuncRising() {
  dbg("swFuncRising()");
}

void swFuncFalling() {
  dbg("swFuncFalling()");
}

void piO1Rising() {
  dbg("piO1Rising()");
  String S = "booted.";
  clearBmp();
  OLD_print5x7(S, 0, 5);
  OLED_display(graphic);
}

void piO1Falling() {
  dbg("piO1Falling()");
  String S = "Bye!";
  String S1 = "";
  String S2 = "";

  clearBmp();
  OLD_print5x7(S, 0, 5);
  OLED_display(graphic);
  //  delay(SHUTDOWN_DELAY_MS);

  long start = millis();

  while (1) {
    long now = millis();

    if (((start + SHUTDOWN_DELAY_MS) - now) % 100 == 0) {
      S1 = "Shutdown in";
      S2 = String((((start + SHUTDOWN_DELAY_MS) - now) / 1000.0), 1);
      S2 += "sec";

      clearBmp();
      OLD_print5x7(S1, 0, 1);
      OLD_print5x7(S2, 0, 9);
      OLED_display(graphic);
    }

    if ((start + SHUTDOWN_DELAY_MS) < now ) {
      break;
    }
  }
  digitalWrite(PI_PWR_PIN, LOW);
  digitalWrite(PI_I01_PIN, LOW);
  S = "bye!";
  clearBmp();
  OLD_print5x7(S, 0, 5);
  OLED_display(graphic);
  delay(1000);
  S = "";
  clearBmp();
  OLD_print5x7(S, 0, 5);
  OLED_display(graphic);
}


void piBoot() {
  dbg("piBoot()");

}

void piShutDown() {
  int interval = 10000;
  dbg("piShutDown()");

  String S = "Shutdown...";
  clearBmp();
  OLD_print5x7(S, 0, 5);
  OLED_display(graphic);

  digitalWrite(PI_I01_PIN, HIGH);
}


void bootUpMessage() {


}



/*******************************************************************
 SERIALs
 *******************************************************************/

void serialInit() {
  // initialize serial:
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);

  // reserve 200 bytes for the strSeriaIncoming1:
  strSeriaIncoming.reserve(200);
  strSeriaIncoming1.reserve(200);
  strSeriaIncoming2.reserve(200);
  strSeriaIncoming3.reserve(200);

}

void serialCheck() {
  serialIncomingCheck();
  serialIncomingCheck1();
  serialIncomingCheck2();
  serialIncomingCheck3();
  serialComplete();
}


void serialIncomingCheck() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    strSeriaIncoming += inChar;
    if (inChar == '\n') {
      blnStringComplete = true;
    }
  }
}

void serialIncomingCheck1() {
  while (Serial1.available()) {
    char inChar = (char)Serial1.read();
    strSeriaIncoming1 += inChar;
    if (inChar == '\n') {
      blnStringComplete1 = true;
    }
  }
}

void serialIncomingCheck2() {
  while (Serial2.available()) {
    char inChar = (char)Serial2.read();
    strSeriaIncoming2 += inChar;
    if (inChar == '\n') {
      blnStringComplete2 = true;
    }
  }
}

void serialIncomingCheck3() {
  while (Serial3.available()) {
    char inChar = (char)Serial3.read();
    strSeriaIncoming3 += inChar;
    if (inChar == '\n') {
      blnStringComplete3 = true;
    }
  }
}

void serialComplete() {
  // Serial USB
  if (blnStringComplete) {
    serialCommandRecieve(strSeriaIncoming);
    strSeriaIncoming = "";
    blnStringComplete = false;
  }
  // Serial 1
  if (blnStringComplete1) {
    serialCommandRecieve1(strSeriaIncoming1);
    strSeriaIncoming1 = "";
    blnStringComplete1 = false;
  }
  // Serial2
  if (blnStringComplete2) {
    serialCommandRecieve2(strSeriaIncoming2);
    strSeriaIncoming2 = "";
    blnStringComplete2 = false;
  }
  // Serial3
  if (blnStringComplete3) {
    serialCommandRecieve3(strSeriaIncoming3);
    strSeriaIncoming3 = "";
    blnStringComplete3 = false;
  }
}

void serialCommandRecieve(String command) {
  dbg("Rx<\t" + command);

}
void serialCommandRecieve1(String command) {
  dbg("Rx1<\t" + command);

}
void serialCommandRecieve2(String command) {
  dbg("Rx2<\t" + command);

}
void serialCommandRecieve3(String command) {
  dbg("Rx3<\t" + command);

}

void dbg(String text) {
  Serial1.print(millis());
  Serial1.print('\t');
  Serial1.print(text);
}
void dbgln(String text) {
  Serial1.print(millis());
  Serial1.print('\t');
  Serial1.println(text);
}



/* =======================================================================================
 setup
=========================================================================================== */
void setup()
{

  delay(5000);
  serialInit();
  pinInit();

  Serial1.println("Start-------------------------------------------------");
  bootUpMessage();




}






/* =======================================================================================
 loop
=========================================================================================== */
void loop()
{


  polling();
  serialCheck();




}
// -- END OF CODE ----------------------------------------------------------
