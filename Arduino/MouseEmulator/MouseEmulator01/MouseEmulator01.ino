/* -----------------------------------------------------------------------------
  (C) Copyright by the respective owner
  ------------------------------------------------------------------------------
  Controls the mouse from five pushbuttons on an Arduino Leonardo, Micro or Due.

  Hardware:
  - five pushbuttons attached to D2, D3, D4, D5, D6

  The mouse movement is always relative. This sketch reads four pushbuttons, and
  uses them to set the movement of the mouse.

  WARNING: When you use the Mouse.move() command, the Arduino takes over your
  mouse! Make sure you have control before you use the mouse commands.

  created 15 Mar 2012
  modified 27 Mar 2012
  by Tom Igoe

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/usb/KeyboardAndMouseControl/
  --------------------------------------------------------------------------- */
#if not defined(ARDUINO_AVR_LEONARDO)
  #error "only for ARDUINO_AVR_LEONARDO"
#endif
// -----------------------------------------------------------------------------
#include "Mouse.h"
// -----------------------------------------------------------------------------
#define MAX_COUNT 3
uint16_t uCount = 0;
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void setup() {
  Mouse.begin();
}
// -----------------------------------------------------------------------------
void loop() {
  delay(5000);
  // move top left
  //Mouse.move(-1000, -1000);
  while (uCount < MAX_COUNT) {
    // click tab
    delay(500);
    //Mouse.move(0, -40);
    delay(500);
    //Mouse.click(MOUSE_LEFT);
    // click tab
    delay(500);
    //Mouse.move(0, -40);
    delay(500);
    //Mouse.click(MOUSE_LEFT);
    // click
    delay(500);
    //Mouse.move(0, -40);
    delay(500);
    //Mouse.click(MOUSE_LEFT);
    // click
    delay(500);
    //Mouse.move(0, -40);
    delay(500);
    //Mouse.click(MOUSE_LEFT);
    uCount = uCount + 1;
  }
}
// -----------------------------------------------------------------------------
