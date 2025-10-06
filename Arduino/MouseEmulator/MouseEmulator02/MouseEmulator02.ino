/* -----------------------------------------------------------------------------
  (C) Copyright by the respective owner
  ------------------------------------------------------------------------------
  Controls the mouse from an Arduino Leonardo, Micro or Due.
  The mouse movement is always relative. 
  WARNING: When you use the Mouse.move() command, the Arduino takes over your
  mouse! Make sure you have control before you use the mouse commands.
  https://docs.arduino.cc/built-in-examples/usb/KeyboardAndMouseControl/
  --------------------------------------------------------------------------- */
#if not defined(ARDUINO_AVR_MICRO)
#error "only for ARDUINO_AVR_MICRO"
#endif
// -----------------------------------------------------------------------------
#include "Mouse.h"
// -----------------------------------------------------------------------------
#define SWITCH_INPUT 4
// -----------------------------------------------------------------------------
#define MOVE_UPPER_LEFT_X -640
#define MOVE_UPPER_LEFT_Y -480
#define CLICK_OVERVIEW_X_ABS 100
#define CLICK_OVERVIEW_Y_ABS 60
#define CLICK_UTILITIES_X_REL 335
#define CLICK_UTILITIES_Y_REL 0
#define CLICK_CONFIGURATION_X_REL -295
#define CLICK_CONFIGURATION_Y_REL 155
#define CLICK_CLOSE_X_REL 335
#define CLICK_CLOSE_Y_REL 220
// -----------------------------------------------------------------------------
bool bFirstRound = true;
// -----------------------------------------------------------------------------
void MouseMove16(int_fast16_t x, int_fast16_t y) {
  int_fast16_t x_moved = 0;
  int_fast16_t y_moved = 0;
  digitalWrite(LED_BUILTIN, HIGH);
  while ((x_moved != x) || (y_moved != y)) {
    // handle x movement by one pixel step
    if ((x > 0) && (x != x_moved)) {
      // move to the right
      Mouse.move(1, 0);
      x_moved++;
    } else if ((x < 0) && (x != x_moved)) {
      // move to the left
      Mouse.move(-1, 0);
      x_moved--;
    } else {
      // no more x move
    }
    if ((y > 0) && (y != y_moved)) {
      // move to the right
      Mouse.move(0, 1);
      y_moved++;
    } else if ((y < 0) && (y != y_moved)) {
      // move to the left
      Mouse.move(0, -1);
      y_moved--;
    } else {
      // no more y move
    }
    //delay(5);
  }
  digitalWrite(LED_BUILTIN, LOW);
}
// -----------------------------------------------------------------------------
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SWITCH_INPUT, INPUT_PULLUP);
  Mouse.begin();
  delay(1000);
  bFirstRound = true;
}
// -----------------------------------------------------------------------------
void loop() {
  if (!digitalRead(SWITCH_INPUT)) {
    if (bFirstRound) {
      MouseMove16(MOVE_UPPER_LEFT_X, MOVE_UPPER_LEFT_Y);        // move upper left
      MouseMove16(CLICK_OVERVIEW_X_ABS, CLICK_OVERVIEW_Y_ABS);  // move to overview
      bFirstRound = false;
    }
    delay(1000);
    Mouse.click(MOUSE_LEFT);
    MouseMove16(CLICK_UTILITIES_X_REL, CLICK_UTILITIES_Y_REL);  // move to utilties
    delay(1000);
    Mouse.click(MOUSE_LEFT);
    MouseMove16(CLICK_CONFIGURATION_X_REL, CLICK_CONFIGURATION_Y_REL);  // move to configuration
    delay(1000);
    Mouse.click(MOUSE_LEFT);
    MouseMove16(CLICK_CLOSE_X_REL, CLICK_CLOSE_Y_REL);  // move to close
    delay(1000);
    Mouse.click(MOUSE_LEFT);
    MouseMove16(-CLICK_UTILITIES_X_REL - CLICK_CONFIGURATION_X_REL - CLICK_CLOSE_X_REL, -CLICK_UTILITIES_Y_REL - CLICK_CONFIGURATION_Y_REL - CLICK_CLOSE_Y_REL);  // move back to overview
  } else {
    bFirstRound = true;
  }
}
// -----------------------------------------------------------------------------
