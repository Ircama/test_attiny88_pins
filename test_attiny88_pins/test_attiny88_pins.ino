/*
 * Test ATTINY88 digital and analog pin values via SH1106 128x64 OLED display
 *
 * Used Libraries:
 * https://github.com/notisrac/SH1106Lib (No buffer SH1106 OLED display driver)
 * https://playground.arduino.cc/Main/SoftwareI2CLibrary/ (required library of SH1106Lib - I2C Master)
 * https://github.com/notisrac/TinyPrint (required library of SH1106Lib)
 */

// softwareI2C lib
#define I2C_HARDWARE 1
#define I2C_TIMEOUT 10
#define I2C_MAXWAIT 10
#define I2C_PULLUP 1
#define I2C_FASTMODE 1
#define SDA_PORT PORTC
#define SDA_PIN 4 // = A4
#define SCL_PORT PORTC
#define SCL_PIN 5 // = A5

// tinyprint lib
#define TP_PRINTLINES 0
#define TP_FLASHSTRINGHELPER 1
#define TP_NUMBERS 1
#define TP_FLOAT 1
#define TP_WINDOWSLINEENDS 0

#include "SH1106Lib.h" // 128x64
#include "glcdfont.h" // FONT5X7_H https://github.com/adafruit/Adafruit-GFX-Library/blob/master/glcdfont.c
#include <TinyPrint.h>
SH1106Lib display;

/*-------------------------------------------------------------------------------------------------------*/
void setup() {
  display.initialize();
  display.clearDisplay();
  display.setFont(font, 5, 7);
  display.setTextWrap(true);
  display.setTextColor(WHITE, TRANSPARENT);
  display.clearDisplay();

  for(int i=0;i<17;i++) {
    pinMode(i, INPUT_PULLUP);
  }
} // setup

#define MULT_DIGITAL 7
#define MULT_ANALOG 6 * MULT_DIGITAL
#define ANALOG_PER_LINE 3 // 128 / MULT_ANALOG = 128 / (6*7) = 3
#define ANALOG_PINS 8
int i, j, analogPin, y;
/*-------------------------------------------------------------------------------------------------------*/
void loop() {
  //display.clearDisplay();
  for(i=0; i<16; i++) {
    display.setCursor(i*MULT_DIGITAL, 0);
    if (i<10)
      display.print(i, DEC);
    else
      display.print(i-10, DEC);
    display.fillRect(i*MULT_DIGITAL, 14, MULT_DIGITAL, 7, BLACK);
    display.setCursor(i*MULT_DIGITAL, 14);
    if (digitalRead(i) == HIGH) {
      display.print("1");
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else {
      display.print("0");
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  i=0;
  y=28;
  for (analogPin=0;analogPin<ANALOG_PINS;analogPin++) {
    display.fillRect(i * MULT_ANALOG, y, (i+1) * MULT_ANALOG - 1, 7, BLACK);
    display.setCursor(i++ * MULT_ANALOG, y);
    display.print(analogRead(analogPin), DEC);
    if (i==ANALOG_PER_LINE) {
      i=0;
      y+=10;
    }
  }
  delay(100);
}
