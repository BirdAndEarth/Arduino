#include <MIDI.h>

boolean note[128];
int     velo[128];

#define C1  36
#define CS1 37
#define D1  38
#define DS1 39
#define E1  40

int p1 = 8;
int p2 = 9;
int p3 = 10;
int p4 = 11;
int p5 = 12;


MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midi1);

void setup()
{
  ini();
  midi1.begin();
  midi1.turnThruOff();
  pinMode(13, OUTPUT);
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);
  pinMode(p5, OUTPUT);
}

void loop()
{
  uint8_t code;
  uint8_t ch, data1, data2;
  ch = 1;         //Read channel set;
  if (midi1.read()) {
    midi1.setInputChannel(ch);  // Channel
    switch (midi1.getType()) {

      case midi::NoteOn:
        data1 = midi1.getData1();    // note no
        data2 = midi1.getData2();    // velocity
        aPlay((int)data1, (int)data2);
        break;

      case midi::NoteOff:
        data1 = midi1.getData1();       // note no
        aStop((int)data1);
        break;
      default:
        break;
    }
  }
}


void aPlay(int no, int ve)
{
  switch (no) {
    case C1:
      digitalWrite(p1, HIGH);
      break;
    case CS1:
      digitalWrite(p2, HIGH);
      break;
    case D1:
      digitalWrite(p3, HIGH);
      break;
    case DS1:
      digitalWrite(p4, HIGH);
      break;
    case E1:
      digitalWrite(p5, HIGH);
      break;
    default:
      break;
  }
}


void aStop(int no) {
  switch (no) {
    case C1:
      digitalWrite(p1, LOW);
      break;
    case CS1:
      digitalWrite(p2, LOW);
      break;
    case D1:
      digitalWrite(p3, LOW);
      break;
    case DS1:
      digitalWrite(p4, LOW);
      break;
    case E1:
      digitalWrite(p5, LOW);
      break;
    default:
      break;
  }
}


void ini()
{
  for (int i = 0; i <= 127; i++) {
    note[i] = false;
    velo[i] = 0;
  }
}
