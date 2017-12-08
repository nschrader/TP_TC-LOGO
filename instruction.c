#include "stdlib.h"
#include "math.h"

#include "instruction.h"

#define ANGLE_CIRCLE 360

Cursor* newCursor(double x, double y, double a) {
  Cursor* new = malloc(sizeof(Cursor));
  new->x = x;
  new->y = y;
  new->a = a;
  return new;
}

Cursor* doForward(Cursor cursor, uint value) {
  Cursor* new = newCursor(cursor.x, cursor.y, cursor.a);
  new->x += value*cos(new->a);
  new->y += value*sin(new->a);
  return new;
}

static void doTurn(Cursor* cursor, int value) {
  cursor->a = (value + cursor->a) % ANGLE_CIRCLE;
}

void doLeft(Cursor* cursor, uint value) {
  doTurn(cursor, value);
}

void doRight(Cursor* cursor, uint value) {
  doTurn(cursor, -value);
}
