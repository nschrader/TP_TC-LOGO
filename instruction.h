#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

typedef unsigned int uint;
typedef struct {
  double x;
  double y;
  int a;
} Cursor;

Cursor* newCursor(double x, double y, double a);
Cursor* doForward(Cursor cursor, uint value);
void doLeft(Cursor* cursor, uint value);
void doRight(Cursor* cursor, uint value);

#endif
