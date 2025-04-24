#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display configuration
#define SCREEN_WIDTH 128  // OLED display width in pixels
#define SCREEN_HEIGHT 64  // OLED display height in pixels
#define OLED_RESET    -1  // Reset pin (or -1 if not used)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Timing variables for tracking time using millis
unsigned long previousMillis = 0;     // stores the last time the clock was updated
const unsigned long interval = 1000;  // interval at which to update (1 second)

// Variables to track hours, minutes, and seconds
int seconds = 0;
int minutes = 0;
int hours = 0;

void setup() {
  Serial.begin(9600);
  
  // Initialize the OLED display at I2C address 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (true); // Halt execution if OLED is not found
  }
  
  // Clear display buffer
  display.clearDisplay();
  display.display();
}

void loop() {
  // Get the current time in milliseconds
  unsigned long currentMillis = millis();
  
  // Check if one second has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    // Increment seconds and handle rollovers for minutes and hours
    seconds++;
    if (seconds >= 60) {
      seconds = 0;
      minutes++;
    }
    if (minutes >= 60) {
      minutes = 0;
      hours++;
    }
    if (hours >= 24) {
      hours = 0;
    }
    
    // Format time as HH:MM:SS
    char timeStr[9];  // 8 characters for HH:MM:SS plus a null terminator
    sprintf(timeStr, "%02d:%02d:%02d", hours, minutes, seconds);
    
    // Clear the display buffer
    display.clearDisplay();
    
    // Set text properties (setTextSize(2) makes the text larger)
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    
    // Calculate text dimensions to center the clock on the display
    int16_t x1, y1;
    uint16_t textWidth, textHeight;
    display.getTextBounds(timeStr, 0, 0, &x1, &y1, &textWidth, &textHeight);
    int x = (SCREEN_WIDTH - textWidth) / 2;
    int y = (SCREEN_HEIGHT - textHeight) / 2;
    
    // Set the cursor to the centered position and print the time string
    display.setCursor(x, y);
    display.print(timeStr);
    
    // Send the buffer to the display
    display.display();
  }
}