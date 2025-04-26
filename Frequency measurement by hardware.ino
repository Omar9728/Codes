#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display configuration
#define SCREEN_WIDTH 128  // OLED display width in pixels
#define SCREEN_HEIGHT 64  // OLED display height in pixels
#define OLED_RESET    -1  // Reset pin (or -1 if not used)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    

byte overF=0;
unsigned long freq;
double period;
// Variables to track hours, minutes, and seconds

void setup() {
  Serial.begin(9600);
   OCR0A = 249;
  TCCR0A = _BV(WGM00) | _BV(WGM01) | _BV(COM0A0); //   
  TCCR0B = _BV(WGM02) | _BV(CS02) | _BV(CS01);  //  PWM mode, input T0 pin D4
  pinMode(6, OUTPUT);   //AIN0
    //250 Hz - timer2
  OCR2A =249;
  OCR2B = 125;  
  TCCR2A = _BV(COM2B1) | _BV(COM2B0) | _BV(WGM21) | _BV(WGM20);  //output D3 in phase, fast PWM mode
  TCCR2B = _BV(WGM22) | _BV(CS22) | _BV(CS21); // set prescaler to 256 and start the timer
  pinMode(3, OUTPUT);
      //  counter input T1 pin D5
  OCR1A = 32767;   //32768 counts
  TCCR1A = _BV(WGM10) | _BV(WGM11) | _BV(COM1A0); //   
  TCCR1B =_BV(WGM12) | _BV(WGM13) | _BV(CS12) | _BV(CS11); //input pin D5
  pinMode(9, OUTPUT);
  Serial.println("Frequency Counter");





  // Initialize the OLED display at I2C address 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (true); // Halt execution if OLED is not found
  }
  
  // Clear display buffer
  display.clearDisplay();
  display.display();
}
void ReadFreq() {
    //wait for high
  while(digitalRead(6)){}
  while(!digitalRead(6)){}
    //start the count
  TIFR1 = _BV(OCF1A);    //reset int
  OCR1A = 32767; 
  TCNT1=0;
  overF=0;
  while(digitalRead(6)){
  if(TIFR1 & (1<<OCF1A)) {++overF; TIFR1 = _BV(OCF1A);}   //overflow 
  } 
      //count end
  freq = (unsigned long)TCNT1 + ((unsigned long)overF * 32768);
  period = 1000000 / (double)freq;
  if(freq == 0){period=0;}
}

void loop() {
    ReadFreq();
  Serial.print("F= "); Serial.println(freq);


    char buf[16];
  if (freq>1000000){
  display.println("f = " + String(freq / 1000000.0, 2) + " MHz");
  display.display();
  }
  else if (freq>1000){
    display.println("f = " + String(freq / 1000.0, 2) + " kHz");
    display.display();}
  
  else {
  display.println("f = " + String(freq) + " Hz")
  }
}
  // 2. Clear and set text properties
  display.clearDisplay();
  display.setTextSize(2);              // adjust size as needed
  display.setTextColor(SSD1306_WHITE);

  // 3. Center the text
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(buf, 0, 0, &x1, &y1, &w, &h);
  int16_t x = (SCREEN_WIDTH  - w) / 2;
  int16_t y = (SCREEN_HEIGHT - h) / 2;
  display.setCursor(x, y);

  // 4. Print to the buffer and push to the screen
  display.print(buf);
  display.display();

   // update rate
}