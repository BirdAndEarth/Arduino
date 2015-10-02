#include <SoftwareSerial.h>

#define ADD_TAG_CODE "02005BF460CD" //change this ID with your own card TAG
#define DEL_TAG_CODE "210014E2BD6A"  //change this ID with your own card TAG

SoftwareSerial rfid = SoftwareSerial(5, 6);
String msg;
String ID ;  //string to store allowed cards

void setup()  
{
  Serial.begin(9600);
  Serial.println("Serial Ready");

  rfid.begin(9600);
  Serial.println("RFID Ready");
}

char c;

void loop(){
  
  while(rfid.available()>0){
    c=rfid.read(); 
    msg += c;
    //Serial.println(msg);  
    //Serial.println(msg.length());
    delay(1);
  }
  msg=msg.substring(1,13);
  if(msg.indexOf(ADD_TAG_CODE)>=0) add(); 
  else if(msg.indexOf(DEL_TAG_CODE)>=0) del();  
  else if(msg.length()>10) verifica();
  msg="";
  
}

void add(){
  Serial.print("What TAG do you wanna grant access?: ");
  msg="";
  while(msg.length()<13){
    while(rfid.available()>0){
      c=rfid.read(); 
      msg += c;
    }
  }
  if(ID.indexOf(msg)>=0) {
    Serial.println("\nAccess already granted for this card.");
    msg="";
  }
  else{
    Serial.print("Card: ");
    Serial.println(msg); 
    ID += msg;
    ID += ",";
    //Serial.print("ID: ");
   // Serial.println(ID);
    msg="";
    Serial.println("Access granted for this card.");
  }

}

void del(){
  msg="";
  Serial.print("What TAG do you wanna deny access?: ");
  while(msg.length()<13){
    while(rfid.available()>0){
      c=rfid.read(); 
      msg += c;
    }
  }
  msg=msg.substring(1,13);
  if(ID.indexOf(msg)>=0){
    Serial.println(msg);
    Serial.println("TAG found. Access for this card denied.");
    //ID.replace(card,"");
    int pos=ID.indexOf(msg);
    msg="";
    msg += ID.substring(0,pos);
    msg += ID.substring(pos+15,ID.length());
    ID="";
    ID += msg;
    //Serial.print("ID: ");
    //Serial.println(ID);
  } else Serial.println("\nTAG not found or already denied");
  msg="";
}

void verifica(){
    msg=msg.substring(1,13);
    if(ID.indexOf(msg)>=0) Serial.println("Access granted.");
    
    else Serial.println("Access denied.");
}
