#include <MIDI.h>

int pinDB    = 8;
int pinSN1   = 9;
int pinSN2   = 10;
int pinHH    = 11;
int pinCR    = 12;
int ledPin   = 13;

const uint8_t noteDB   = 36;
const uint8_t noteSN1  = 38;
const uint8_t noteSN2  = 40;
const uint8_t noteHH   = 42;
const uint8_t noteCR   = 49;

boolean flgHH = false;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midi1);

void setup()
{
  midi1.begin();
  midi1.turnThruOff();
  pinMode(13, OUTPUT);
  pinMode(pinDB, OUTPUT);
  pinMode(pinSN1, OUTPUT);
  pinMode(pinSN2, OUTPUT);
  pinMode(pinHH, OUTPUT);
  pinMode(pinCR, OUTPUT);
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
    case noteDB:
      digitalWrite(pinDB, HIGH);
      ledOn();
      break;
    case noteSN1:
      digitalWrite(pinSN1, HIGH);
      ledOn();
      break;
    case noteSN2:
      digitalWrite(pinSN2, HIGH);
      ledOn();
      break;
    case noteHH:
      flgHH = !flgHH;
      digitalWrite(pinHH, flgHH);
      digitalWrite(ledPin, flgHH);
      break;
    case noteCR:
      digitalWrite(pinCR, HIGH);
      ledOn();
      break;
    default:
      break;
  }
}


void aStop(int no) {
  switch (no) {
    case noteDB:
      digitalWrite(pinDB, LOW);
      ledOff();
      break;
    case noteSN1:
      digitalWrite(pinSN1, LOW);
      ledOff();
      break;
    case noteSN2:
      digitalWrite(pinSN2, LOW);
      ledOff();
      break;
    case noteHH:
      // digitalWrite(pinHH, LOW);
      // ledOff();
      break;
    case noteCR:
      digitalWrite(pinCR, LOW);
      ledOff();
      break;
    default:
      break;
  }
}

void ledOn() {
  digitalWrite(ledPin, HIGH);
}

void ledOff() {
  digitalWrite(ledPin, LOW);
}

/*
NOTE 　No
G8   127
F#8  126
F8   125
E8   124
D#8  123
D8   122
C#8  121
C8   120
B7   119
A#7  118
A7   117
G#7  116
G7   115
F#7  114
F7   113
E7   112
D#7  111
D7   110
C#7  109
C7   108
B6   107
A#6  106
A6   105
G#6  104
G6   103
F#6  102
F6   101
E6   100
D#6   99
D6    98
C#6   97
C6    96
B5    95
A#5   94
A5    93
G#5   92
G5    91
F#5   90
F5    89
E5    88
D#5   87
D5    86
C#5   85
C5    84
B4    83
A#4   82
A4    81
G#4   80
G4    79
F#4   78
F4    77
E4    76
D#4   75
D4    74
C#4   73
C4    72
B3    71
A#3   70
A3    69
G#3   68
G3    67
F#3   66
F3    65
E3    64
D#3   63
D3    62
C#3   61
C3    60
B2    59
A#2   58
A2    57
G#2   56
G2    55
F#2   54
F2    53
E2    52
D#2   51
D2    50
C#2   49
C2    48
B1    47
A#1   46
A1    45
G#1   44
G1    43
F#1   42
F1    41
E1    40
D#1   39
D1    38
C#1   37
C1    36
B0    35
A#0   34
A0    33
G#0   32
G0    31
F#0   30
F0    29
E0    28
D#0   27
D0    26
C#0   25
C0    24
B-1   23
A#-1  22
A-1   21
G#-1  20
G-1   19
F#-1  18
F-1   17
E-1   16
D#-1  15
D-1   14
C#-1  13
C-1   12
B-2   11
A#-2  10
A-2    9
G#-2   8
G-2    7
F#-2   6
F-2    5
E-2    4
D#-2   3
D-2    2
C#-2   1
C-2    0

*/

// -- EOF --
