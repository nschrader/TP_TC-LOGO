#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "main.h"

typedef struct _Point {
  double x;
  double y;
  struct _Point* next;
} Point;

typedef struct {
  //Current position of the cursor
  double x;
  double y;
  int a;

  //Gathered information about the path
  double xOrigin;
  double yOrigin;
  double width;
  double height;
  Point* points;
} Cursor;

Point* newPoint(double x, double y, Point* next);
void addPoint(Cursor* cursor);

Cursor* newCursor();
void cursorForward(Cursor* cursor, uint value);
void cursorLeft(Cursor* cursor, uint value);
void cursorRight(Cursor* cursor, uint value);
void freeCursor(Cursor* cursor);

#endif
