#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "instruction.h"

#define ANGLE_CIRCLE 360
#define TO_RADIANS(x) (x * M_PI / 180.0)
#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x > y ? x : y)

Point* newPoint(double x, double y, Point* next) {
  Point* new = malloc(sizeof(Point));
  new->x = x;
  new->y = y;
  new->next = next;
  return new;
}

void addPoint(Cursor* cursor) {
  cursor->points = newPoint(cursor->x, cursor->y, cursor->points);
  cursor->xMin = MIN(cursor->x, cursor->xMin);
  cursor->yMin = MIN(cursor->y, cursor->yMin);
  cursor->xMax = MAX(cursor->x, cursor->xMax);
  cursor->yMax = MAX(cursor->y, cursor->yMax);
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

void freeCursor(Cursor* cursor) {
  while(cursor->points != NULL) {
    Point* point = cursor->points;
    cursor->points = cursor->points->next;
    free(point);
  }
  free(cursor);
}
