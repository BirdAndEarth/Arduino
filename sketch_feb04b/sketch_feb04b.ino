/* SUPER FAST ON/OFF */


/*
 PB 01234567
 PC ------67
 PD 01234567
 PE --2---6-
 PF 01--4567
 
 DDRx
 PORTx
 PINx
 */


void setup() {
}

void loop() {
}

void xsetport(){

  //INPUT = 0, OUTPUT = 1
  //PB     76543210
  DDRB |= B00000000;

  //PC     76------   
  DDRC |= B00000000;

  //PD     76543210
  DDRD |= B00000000;

  //PE     -6---2--
  DDRE |= B00000000;

  //PF     7654--10 
  DDRF |= B00000000;


}

