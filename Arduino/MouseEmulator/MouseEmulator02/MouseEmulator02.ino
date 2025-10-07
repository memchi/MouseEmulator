/* -----------------------------------------------------------------------------
  (C) Copyright by the respective owner
  ------------------------------------------------------------------------------
  Controls the mouse from an Arduino Leonardo, Micro or Due.
  The mouse movement is always relative.
  WARNING: When you use the Mouse.move() command, the Arduino takes over your
  mouse! Make sure you have control before you use the mouse commands.
  https://docs.arduino.cc/built-in-examples/usb/KeyboardAndMouseControl/
  https://docs.arduino.cc/language-reference/en/functions/usb/Mouse/
  --------------------------------------------------------------------------- */
#if not defined(ARDUINO_AVR_MICRO)
  #error "only for ARDUINO_AVR_MICRO"
#endif
// -----------------------------------------------------------------------------
#include "Mouse.h"
//#include "Tracing.h"
#include "TracingStub.h"
// -----------------------------------------------------------------------------
#define SWITCH_INPUT 4  // port where to switch functionality on (PULL to ground)
// -----------------------------------------------------------------------------
#define TO_ORIGIN_X -640  // in mickeys (not a const factor to pixels, could be accelerated)
#define TO_ORIGIN_Y -480
#define FROM_ORIGIN_TO_OVERVIEW_X 105
#define FROM_ORIGIN_TO_OVERVIEW_Y 55
#define FROM_OVERVIEW_TO_UTILITIES_X 570
#define FROM_OVERVIEW_TO_UTILITIES_Y 0
#define FROM_UTILITIES_TO_CONFIGURATION_X -385
#define FROM_UTILITIES_TO_CONFIGURATION_Y 140
#define FROM_CONFIGURATION_TO_CLOSE_X 400
#define FROM_CONFIGURATION_TO_CLOSE_Y 200
// speed settings
#define MOUSE_STEP_PIXELS 10
#define MILLISEC_PER_MOUSE_STEP 25
// calibrate sometimes to origin
#define CALIBRATE_EVERY 20
// -----------------------------------------------------------------------------
uint_fast16_t uRoundSinceCalibration = 0;
// -----------------------------------------------------------------------------
// original Mouse.move only uses signed char (+- 127), MouseMove16 provides int_fast16_t (+- 32k)
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
    if (uRoundSinceCalibration >= CALIBRATE_EVERY) {
      uRoundSinceCalibration = 0;
    }
    if (uRoundSinceCalibration == 0) {
      // calibrate with moving further than upper left
      MouseMove16(TO_ORIGIN_X, TO_ORIGIN_Y);
      MouseMove16(FROM_ORIGIN_TO_OVERVIEW_X, FROM_ORIGIN_TO_OVERVIEW_Y);
    } else {
      // move same path backwards to avoid misalignement with acceleration
      MouseMove16(-FROM_CONFIGURATION_TO_CLOSE_X, -FROM_CONFIGURATION_TO_CLOSE_Y);
      MouseMove16(-FROM_UTILITIES_TO_CONFIGURATION_X, -FROM_UTILITIES_TO_CONFIGURATION_Y);
      MouseMove16(-FROM_OVERVIEW_TO_UTILITIES_X, -FROM_OVERVIEW_TO_UTILITIES_Y);
    };
    delay(100);
    Mouse.click(MOUSE_LEFT);
    MouseMove16(FROM_OVERVIEW_TO_UTILITIES_X, FROM_OVERVIEW_TO_UTILITIES_Y);
    delay(100);
    Mouse.click(MOUSE_LEFT);
    MouseMove16(FROM_UTILITIES_TO_CONFIGURATION_X, FROM_UTILITIES_TO_CONFIGURATION_Y);
    delay(100);
    Mouse.click(MOUSE_LEFT);
    MouseMove16(FROM_CONFIGURATION_TO_CLOSE_X, FROM_CONFIGURATION_TO_CLOSE_Y);
    delay(100);
    Mouse.click(MOUSE_LEFT);
    uRoundSinceCalibration = uRoundSinceCalibration + 1;
  } else {
    uRoundSinceCalibration = 0;
  }
  delay(100);
  TRACE(tlDEBUG, pfEND, "");
}
// -----------------------------------------------------------------------------
