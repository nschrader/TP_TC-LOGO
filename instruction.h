#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "main.h"

typedef struct {
  double x;
  double y;
  int a;
} Cursor;

Cursor* newCursor(double x, double y, double a);
Cursor* cursorForward(const Cursor* cursor, uint value);
void cursorLeft(Cursor* cursor, uint value);
void cursorRight(Cursor* cursor, uint value);

#endif
