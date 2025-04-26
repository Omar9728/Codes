const int FreqPin=2;
long Cnt;
bool PrevState, CurrentState;
long T;
long tloop;
void setup(){

// put your setup code here, to run once:
pinMode (FreqPin, INPUT) ;
Serial. begin (115200);
Cnt=0;

PrevState-false;

CurrentState=0;

T=micros();
}
void loop() {
  tloop=micros();
CurrentState=digitalRead(FreqPin);
if (CurrentState^PrevState){Cnt++;}
PrevState=CurrentState;
if (micros()-T>=1000000){Serial.println(Cnt/2);Cnt=0; T=micros();}
Serial.println("T= "); Serial.println(micros()-tloop);
}