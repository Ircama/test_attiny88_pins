# Test ATTINY88 digital and analog pin values via SH1106 128x64 OLED display connected via I2C

This simple code uses the SH1106 OLED display to show the pin values of an ATTINY88 device. By changing the number of Analog and Digital inputs, also the ATTINY85 (or Digispark) can be supported.

The I2C connection is used to interface the display.

The program continuously reads all the ATTINY pins, providing a dynamic snapshot of the related values to the OLED display.

Used Libraries:

 - https://github.com/notisrac/SH1106Lib (No buffer SH1106 OLED display driver)
 - https://playground.arduino.cc/Main/SoftwareI2CLibrary/ (required library of SH1106Lib - I2C Master)
 - https://github.com/notisrac/TinyPrint (required library of SH1106Lib)
