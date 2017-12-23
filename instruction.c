#include "stdlib.h"
#include "math.h"

#include "instruction.h"

#define ANGLE_CIRCLE 360
#define TO_RADIANS(x) (x * M_PI / 180.0)

Cursor* newCursor(double x, double y, double a) {
  Cursor* new = malloc(sizeof(Cursor));
  new->x = x;
  new->y = y;
  new->a = a;
  return new;
}

Cursor* cursorForward(const Cursor* cursor, uint value) {
  Cursor* new = newCursor(cursor->x, cursor->y, cursor->a);
  new->x += value*cos(TO_RADIANS(new->a));
  new->y += value*sin(TO_RADIANS(new->a));
  return new;
}

static void cursorTurn(Cursor* cursor, int value) {
  cursor->a = (value + cursor->a) % ANGLE_CIRCLE;
}

void cursorLeft(Cursor* cursor, uint value) {
  cursorTurn(cursor, value);
}

void cursorRight(Cursor* cursor, uint value) {
  cursorTurn(cursor, -value);
}
