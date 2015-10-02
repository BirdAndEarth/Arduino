#define DBG 1

String strHeader = "";    // string to hold input
String strData = "";    // string to hold input

boolean bFlgSet = false;
boolean bFlgOut = false;



void setup() {
  // Open Serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
  }

  // send an intro:
  Serial.println("\n\nString toInt():");
  Serial.println();
}

void loop() {
  // Read Serial input:
}



void checkSerial(){
  while (Serial.available() > 0) {
    int inChar = Serial.read();

    // detect

    if (isDigit(inChar) | inChar == 46){
      strData += (char)inChar;
    }
    else{
      switch (inChar){
      case 13:
        updateAdc;
        break;

      case default:
        strHeader += (char)inChar;
        break;
      }
    }
  }
}

void updateAdc(){

  
  char data[strData.length() + 1]; //determine size of the array
  strData.toCharArray(carray, sizeof(data)); //put readStringinto an array
  int n = atoi(data); //convert the array into an Integer 
  float f = atof(data);
  Serial.print("String = ");
  Serial.print(inString);
  Serial.print("\tint = ");
  Serial.print(n);
  Serial.print("\tfloat = ");
  Serial.print(f,4);
  Serial.println("");

  strData = "";
  header






}


void setReferenceVoltage(float data){
}


void setAdcData(float data){
}














