#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>


#define D7 4


void setup() {
  // put your setup code here, to run once:
  MIDI.begin();
 pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    //チャンネル選択
    int beforCh = Ch;
    Ch = 1;
    
    uint8_t data1,data2;
    if (MIDI.read()) {
        MIDI.setInputChannel(Ch);   //読み込むチャンネルを設定
 
        switch(MIDI.getType()) {
            case NoteOn:        //鍵盤を押す
                data1 = MIDI.getData1();    // ノートNo.（音階）
                data2 = MIDI.getData2();    // ベロシティ（音の強さ）
                digitalWrite(13, HIGH);
            break;
            case NoteOff:       //鍵盤を離す
                data1 = MIDI.getData1();    // ノートNo.（音階）
                data2 = MIDI.getData2();    // ベロシティ（音の強さ）
                digitalWrite(13, LOW);
            break;
 
        }
    }
}

