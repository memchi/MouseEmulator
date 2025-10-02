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
#define RECTANGLE_X_SIZE_HALF 200
#define RECTANGLE_Y_SIZE_HALF 100
#define MAX_COUNT 5
#define MOVE_LEFT_TOP 2000
uint16_t uCount = 0;
// -----------------------------------------------------------------------------
void MouseMove16(int_fast16_t x, int_fast16_t y) {
  int_fast16_t x_moved = 0;
  int_fast16_t y_moved = 0;
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
  }
}
// -----------------------------------------------------------------------------
void setup() {
  Mouse.begin();
}
// -----------------------------------------------------------------------------
void loop() {
  delay(2000);
  while (uCount < MAX_COUNT) {
    if (uCount == 0) {
      // start move
      MouseMove16(-RECTANGLE_X_SIZE_HALF, -RECTANGLE_Y_SIZE_HALF);
    }
    // move rectangle
    MouseMove16(RECTANGLE_X_SIZE_HALF * 2, 0);
    MouseMove16(0, RECTANGLE_Y_SIZE_HALF * 2);
    MouseMove16(-(RECTANGLE_X_SIZE_HALF * 2), 0);
    MouseMove16(0, -(RECTANGLE_Y_SIZE_HALF * 2));
    if (uCount == (MAX_COUNT - 1)) {
      // end move
      MouseMove16(RECTANGLE_X_SIZE_HALF, RECTANGLE_Y_SIZE_HALF);
    }
    uCount = uCount + 1;
  }
}
// -----------------------------------------------------------------------------
