#include <SoftwareSerial.h>
char Dta;
SoftwareSerial mySerial(2,3);

void setup() {
  // put your setup code here, to run once:
 Serial.begin(1152000);
 mySerial.begin(9600);
 pinMode(13, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()){
  Dta=Serial.read();
  mySerial.print(Dta);

}
if(mySerial.available()){
  Dta=mySerial.read();
  Serial.print("I received: ");
  Serial.println(Dta);
  if (Dta=='Y'){digitalWrite(13 , HIGH);}
  if (Dta=='N'){digitalWrite(13,  LOW);}

if (Dta>48 and Dta<58){
  for (int i=0;i<Dta-48;i++){
    digitalWrite(13, HIGH);
    delay(250);
    digitalWrite(13, LOW);
    delay(250);
  }
}
}
}