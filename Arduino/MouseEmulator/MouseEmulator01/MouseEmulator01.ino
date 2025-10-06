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
#include "Tracing.h"
// -----------------------------------------------------------------------------
#define SWITCH_INPUT 4
// -----------------------------------------------------------------------------
#define RECTANGLE_X_SIZE_HALF 200
#define RECTANGLE_Y_SIZE_HALF 100
//#define MAX_COUNT 5
//#define MOVE_LEFT_TOP 2000
//uint16_t uCount = 0;
#define MOUSE_STEP_PIXELS 25
#define MILLISEC_PER_MOUSE_STEP 100
// -----------------------------------------------------------------------------
void MouseMove16(int_fast16_t x, int_fast16_t y) {
  TRACE(tlDEBUG, pfSTART, "");
  TRACE(tlINFO, pfNONE, "--------------------------------------------------------------------------------");
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
void setup() {
  //TRACESTART(tlWARNING, 115200);
  TRACESTART(tlINFO, 115200);
  //TRACESTART(tlDEBUG, 115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SWITCH_INPUT, INPUT_PULLUP);
  delay(5000);
  Mouse.begin();
  TRACE(tlDEBUG, pfEND, "");
}
// -----------------------------------------------------------------------------
void loop() {
  TRACE(tlDEBUG, pfSTART, "");
  //TRACE(tlINFO, pfNONE, "Dist: %d mm", 123);
  if (!digitalRead(SWITCH_INPUT)) {
    MouseMove16(RECTANGLE_X_SIZE_HALF, 0);
    delay(500);
    MouseMove16(RECTANGLE_X_SIZE_HALF, RECTANGLE_Y_SIZE_HALF);
    delay(500);
    MouseMove16(0, RECTANGLE_Y_SIZE_HALF);
    delay(500);
    MouseMove16(-RECTANGLE_X_SIZE_HALF, RECTANGLE_Y_SIZE_HALF);
    delay(500);
    MouseMove16(-RECTANGLE_X_SIZE_HALF, 0);
    delay(500);
    MouseMove16(-RECTANGLE_X_SIZE_HALF, -RECTANGLE_Y_SIZE_HALF);
    delay(500);
    MouseMove16(0, -RECTANGLE_Y_SIZE_HALF);
    delay(500);
    MouseMove16(RECTANGLE_X_SIZE_HALF, -RECTANGLE_Y_SIZE_HALF);
    delay(500);
  }
  delay(500);
  TRACE(tlDEBUG, pfEND, "");
}
// -----------------------------------------------------------------------------
