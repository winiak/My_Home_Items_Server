
/**
 * Usin Adafruit_SSD1306 library.
 * Try also other library: https://github.com/ThingPulse/esp8266-oled-ssd1306
 */

//#include <TimeLib.h>

#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"

// I2C: UI address, SDA, SCL
SSD1306Wire  display(0x3c, D2, D1);
uint8_t text_line;
#define MAX_LINES 5
#define MAX_LINE_WIDTH 100
  
void screen_setup() {
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  text_line = 0;

  writeLine("Starting...");
}

void writeLine(String text) {
  if (text_line == MAX_LINES) {
    text_line = 0;
    display.clear();
  }
  //display.drawStringMaxWidth(0, text_line*10, MAX_LINE_WIDTH, text);
  display.drawString(0, text_line*10, text);
  text_line++;
  display.display();
}

/*
// Adafruit
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void screen_setup() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();  
}
*/

