#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "instruction.h"

#define ANGLE_CIRCLE 360
#define TO_RADIANS(x) (x * M_PI / 180.0)

Point* newPoint(double x, double y, Point* next) {
  Point* new = malloc(sizeof(Point));
  new->x = x;
  new->y = y;
  new->next = next;
  return new;
}

void addPoint(Cursor* cursor) {
  cursor->points = newPoint(cursor->x, cursor->y, cursor->points);
  if (cursor->x < cursor->xOrigin) {
    cursor->xOrigin = cursor->x;
  }
  if (cursor->y < cursor->yOrigin) {
    cursor->yOrigin = cursor->y;
  }
  if (cursor->x > cursor->xOrigin + cursor->width) {
    cursor->width = cursor->x - cursor->xOrigin;
  }
  if (cursor->y > cursor->yOrigin + cursor->height) {
    cursor->height = cursor->y - cursor->yOrigin;
  }
}

Cursor* newCursor() {
  Cursor* new = malloc(sizeof(Cursor));
  memset(new, 0, sizeof(Cursor));
  addPoint(new);
  return new;
}

void cursorForward(Cursor* cursor, uint value) {
  cursor->x += value*cos(TO_RADIANS(cursor->a));
  cursor->y -= value*sin(TO_RADIANS(cursor->a));
  addPoint(cursor);
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
