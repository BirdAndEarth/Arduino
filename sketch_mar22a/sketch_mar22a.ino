/*
// MapleMini Port Control Example

  BSRR Set/Reset Register
  BRR  Reset Register


  //on the LED pin(33, PB1):
  GPIOB->regs->BSRR = 0b10; // LED pin33 = PB1

  //off the LED pin(33, PB1):
  GPIOB->regs->BRR  = 0b10; // LED pin33 = PB1

  //OR

  //ON the LED pin(33, PB1):
  //                    |----Reset-----||----Set-------|
  //                    PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
  //                    BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
  //                    111111          111111          
  //                    54321098765432105432109876543210
  GPIOB->regs->BSRR = 0b00000000000000000000000000000010; // LED pin33 = PB1
  //OFF the LED pin(33, PB1):
  //                    |----Reset-----||----Set-------|
  //                    PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
  //                    BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
  //                    111111          111111          
  //                    54321098765432105432109876543210
  GPIOB->regs->BSRR = 0b00000000000000100000000000000000; // LED pin33 = PB1


  
*/
void setup() {
Serial.begin(115200);
pinMode(PB1, OUTPUT);
}

void loop() {
//                    
  //ON the LED pin(33, PB1):
  //                    |----Reset-----||----Set-------|
  //                    PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
  //                    BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
  //                    111111          111111          
  //                    54321098765432105432109876543210
  GPIOB->regs->BSRR = 0b00000000000000000000000000000010; // LED pin33 = PB1
  delay(75);
  //OFF the LED pin(33, PB1):
  //                    |----Reset-----||----Set-------|
  //                    PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
  //                    BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
  //                    111111          111111          
  //                    54321098765432105432109876543210
  GPIOB->regs->BSRR = 0b00000000000000100000000000000000; // LED pin33 = PB1
  delay(75);

}
