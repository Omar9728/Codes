#include <IRremote.h>  //including infrared remote header file 

int IR_RECEIVE_PIN=2;

void setup(){
  pinMode(IR_RECEIVE_PIN, INPUT);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.begin(115200);
}

void loop(){
  ChkIR();
  // Do Something
}

void ChkIR(){
  if (IrReceiver.decode())// Returns 0 if no data ready, 1 if data ready. 
  { 
    int GG = IrReceiver.decodedIRData.decodedRawData;
    int CC = IrReceiver.decodedIRData.command;
    Serial.print("Code: "); Serial.println(CC);
        
    switch (CC) {
      case 22:
        break;
      case 12:
        break;

      default:
        break;
    }
    IrReceiver.resume();
  } 
}