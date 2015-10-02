
int CLK = 2;
int DIN = 3;
int CS  = 4;
int in = 0;

#define MAXBIT 16

int data[MAXBIT];


void setup(){
  pinMode(CLK, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
}



void loop(){

  for(int i = 1; i <= MAXBIT; i++)
  {
    resetAllXbit();
    setXbit(i);
    updateXbit();
    delay(10);
  }

  for(int i = MAXBIT; i >= 1; i--)
  {
    resetAllXbit();
    setXbit(i);
    updateXbit();
    delay(10);
  }
}




/********************************************
 * Low level functions 
 * when you port this program, please change.
 ********************************************/

void setXbit(int b){
  data[b - 1 ] = 1;  
}

void resetXbit(int b){
  data[b - 1 ] = 0; 
}

void resetAllXbit(){
  for (int i = 0; i < MAXBIT; i++){
    data[i] = 0; 
  }
}

void updateXbit(){
  _send(data);
}


void _send(int b[])
{
  __cs(0);
  for (int i = MAXBIT - 1; i >= 0; i--){
    __din((b[i]));
    __clk(1);
    __din(0);
    __clk(0);
  }
  __cs(1);
}

void __cs(int state)
{
  if (state == 1){
    // set cbit on = cs
    digitalWrite(CS, HIGH);
  } 
  else {
    // set cbit off = cs
    digitalWrite(CS, LOW);
  }
}

void __clk(int state)
{
  if (state == 1){
    // set cbit on = clk
    digitalWrite(CLK, HIGH); 
  } 
  else {
    // set cbit off = clk
    digitalWrite(CLK, LOW); 
  }
}

void __din(int state)
{
  if (state == 1){
    // set cbit on = din
    digitalWrite(DIN, HIGH); 
  } 
  else {
    // set cbit off = din
    digitalWrite(DIN, LOW); 
  }
}









