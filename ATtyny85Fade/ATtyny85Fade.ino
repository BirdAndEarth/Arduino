/*
 Fading
 
 This example shows how to fade an LED using the analogWrite() function.
 
 The circuit:
 * LED attached from digital pin 9 to ground.
 
 Created 1 Nov 2008
 By David A. Mellis
 modified 30 Aug 2011
 By Tom Igoe
 
 http://arduino.cc/en/Tutorial/Fading
 
 This example code is in the public domain.
 
 */


int ledPin1 = 0;
int ledPin0 = 1;

void setup()  { 
  // nothing happens in setup 
} 

void loop()  {
  //
  //  for (int i = 0; i < 10 ; i++){
  //    analogWrite(ledPin1, 255);
  //    delay(500);    
  //    analogWrite(ledPin1, 0);         
  //    delay(500);    
  //  }
  //
  //  for (int i = 0; i < 10 ; i++){
  //    analogWrite(ledPin0, 255);
  //    delay(100);    
  //    analogWrite(ledPin0, 0);         
  //    delay(100);    
  //  }
  //
  //  for (int i = 0; i < 10 ; i++){
  //    analogWrite(ledPin0, 255);
  //    analogWrite(ledPin0, 255);
  //    delay(500);    
  //    analogWrite(ledPin0, 0);         
  //    analogWrite(ledPin0, 0);
  //    delay(500);    
  //  }

  for (int i = 0; i < 3 ; i++){
    for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
      analogWrite(ledPin1, fadeValue);         
      delay(10);                            
    }
    delay(300);
    for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
      analogWrite(ledPin1, fadeValue);         
      delay(10);                            
    }
    delay(300);
  }

  for (int i = 0; i < 3 ; i++){
    for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
      analogWrite(ledPin0, fadeValue);         
      delay(10);                            
    }
    delay(300);

    for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
      analogWrite(ledPin0, fadeValue);         
      delay(10);                            
    }
    delay(300);

  }

  for (int i = 0; i < 3 ; i++){
    for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
      analogWrite(ledPin1, fadeValue);         
      analogWrite(ledPin0, fadeValue);         
      delay(10);                            
    } 
    delay(300);

    for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
      analogWrite(ledPin1, fadeValue);         
      analogWrite(ledPin0, fadeValue);         
      delay(10);                            
    }
    delay(300);
  }
}




