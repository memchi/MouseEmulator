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
//#include "Tracing.h"
// -----------------------------------------------------------------------------
// replace tracing
#ifndef TRACESTART
#define TRACESTART(Level, baud) {}
#define TRACE(Level, PosInFunction, ...) {}
#endif
// -----------------------------------------------------------------------------
#define SWITCH_INPUT 4
// -----------------------------------------------------------------------------
#define MOVE_UPPER_LEFT_X -640 // in mickeys (not a const factor to pixels, could be accelerated)
#define MOVE_UPPER_LEFT_Y -480
#define CLICK_OVERVIEW_X 100
#define CLICK_OVERVIEW_Y 50
#define CLICK_UTILITIES_X 670
#define CLICK_UTILITIES_Y 50
#define CLICK_CONFIGURATION_X 290
#define CLICK_CONFIGURATION_Y 190
#define CLICK_CLOSE_X 650
#define CLICK_CLOSE_Y 400
#define MOUSE_STEP_PIXELS 10
#define MILLISEC_PER_MOUSE_STEP 100
// -----------------------------------------------------------------------------
bool bFirstRound = true;
int_fast16_t x_absolute = 0;
int_fast16_t y_absolute = 0;
// -----------------------------------------------------------------------------
void MouseMove16(int_fast16_t x, int_fast16_t y) {
  TRACE(tlDEBUG, pfSTART, "");
  TRACE(tlINFO, pfNONE, "x: %d, y: %d", x, y);
  int_fast16_t x_moved = 0;
  int_fast16_t y_moved = 0;
  digitalWrite(LED_BUILTIN, HIGH);
  while ((abs(x_moved) < abs(x)) || (abs(y_moved) < abs(y))) {
    TRACE(tlINFO, pfNONE, "x_moved: %d, y_moved: %d", x_moved, y_moved);
    // handle x movement by one pixel step
    if ((x > 0) && (abs(x_moved) < abs(x))) {
      // move to the right
      int ActMouseStepPixelsRight = min(x - x_moved, MOUSE_STEP_PIXELS);
      TRACE(tlINFO, pfNONE, "Mouse.move (right), x: %d, y: %d", ActMouseStepPixelsRight, 0);
      Mouse.move(ActMouseStepPixelsRight, 0);
      x_moved = x_moved + ActMouseStepPixelsRight;
    } else if ((x < 0) && (abs(x_moved) < abs(x))) {
      // move to the left
      int ActMouseStepPixelsLeft = max(x - x_moved, -MOUSE_STEP_PIXELS);
      TRACE(tlINFO, pfNONE, "Mouse.move (left), x: %d, y: %d", ActMouseStepPixelsLeft, 0);
      Mouse.move(ActMouseStepPixelsLeft, 0);
      x_moved = x_moved + ActMouseStepPixelsLeft;
    } else {
      // no more x move
    }
    if ((y > 0) && (abs(y_moved) < abs(y))) {
      // move down
      int ActMouseStepPixelsDown = min(y - y_moved, MOUSE_STEP_PIXELS);
      TRACE(tlINFO, pfNONE, "Mouse.move (down), x: %d, y: %d", 0, ActMouseStepPixelsDown);
      Mouse.move(0, ActMouseStepPixelsDown);
      y_moved = y_moved + ActMouseStepPixelsDown;
    } else if ((y < 0) && (abs(y_moved) < abs(y))) {
      // move up
      int ActMouseStepPixelsUp = max(y - y_moved, -MOUSE_STEP_PIXELS);
      TRACE(tlINFO, pfNONE, "Mouse.move (up), x: %d, y: %d", 0, ActMouseStepPixelsUp);
      Mouse.move(0, ActMouseStepPixelsUp);
      y_moved = y_moved + ActMouseStepPixelsUp;
    } else {
      // no more y move
    }
    delay(MILLISEC_PER_MOUSE_STEP);
  }
  digitalWrite(LED_BUILTIN, LOW);
}
// -----------------------------------------------------------------------------
void MouseMoveOrigin() {
  TRACE(tlINFO, pfNONE, "--------------------------------------------------------------------------------");
  MouseMove16(MOVE_UPPER_LEFT_X, MOVE_UPPER_LEFT_Y);  // move upper left
  x_absolute = 0;
  y_absolute = 0;
}
// -----------------------------------------------------------------------------
void MouseMoveAbsolute(int_fast16_t x, int_fast16_t y) {
  TRACE(tlINFO, pfNONE, "--------------------------------------------------------------------------------");
  TRACE(tlINFO, pfNONE, "x: %d, y: %d", x, y);
  TRACE(tlINFO, pfNONE, "x_absolute: %d, y_absolute: %d", x_absolute, y_absolute);
  MouseMove16(x - x_absolute, y - y_absolute);
  x_absolute = x;
  y_absolute = y;
  TRACE(tlINFO, pfNONE, "x_absolute: %d, y_absolute: %d", x_absolute, y_absolute);
}
// -----------------------------------------------------------------------------
void setup() {
  //TRACESTART(tlWARNING, 115200);
  TRACESTART(tlINFO, 115200);
  //TRACESTART(tlDEBUG, 115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SWITCH_INPUT, INPUT_PULLUP);
  Mouse.begin();
  delay(1000);
  TRACE(tlDEBUG, pfEND, "");
}
// -----------------------------------------------------------------------------
void loop() {
  TRACE(tlDEBUG, pfSTART, "");
  if (!digitalRead(SWITCH_INPUT)) {
    if (bFirstRound) {
      MouseMoveOrigin();
      bFirstRound = false;
    }
    MouseMoveAbsolute(CLICK_OVERVIEW_X, CLICK_OVERVIEW_Y);  // move to overview tab
    delay(1000);
    //Mouse.click(MOUSE_LEFT);
    MouseMoveAbsolute(CLICK_UTILITIES_X, CLICK_UTILITIES_Y);  // move to utilties tab
    delay(1000);
    //Mouse.click(MOUSE_LEFT);
    MouseMoveAbsolute(CLICK_CONFIGURATION_X, CLICK_CONFIGURATION_Y);  // move to configuration button
    delay(1000);
    //Mouse.click(MOUSE_LEFT);
    MouseMoveAbsolute(CLICK_CLOSE_X, CLICK_CLOSE_Y);  // move to close button
    delay(1000);
    //Mouse.click(MOUSE_LEFT);
  } else {
    bFirstRound = true;
  }
  TRACE(tlDEBUG, pfEND, "");
}
// -----------------------------------------------------------------------------
