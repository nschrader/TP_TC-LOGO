#include <CUnit/Basic.h>

#include "instruction_test.h"
#include "memory_leak.h"
#include "instruction.h"
#include "misc.h"

void testPointDeconstructor() {
  Point* p;
  p = newPoint(1, 2, NULL);
  p = newPoint(3, 4, p);
  p = newPoint(5, 6, p);
  freePoints(p);
  ASSERT_MEMORY_LEAKS();
}

void testAddPoint() {
  Cursor* c = newCursor();
  addPoint(c);
  c->x = 3;
  c->y = 5;
  addPoint(c);

  CU_ASSERT(c->xMax == 3);
  CU_ASSERT(c->xMin == 0);
  CU_ASSERT(c->yMax == 5);
  CU_ASSERT(c->yMin == 0);
  Point* p = c->points;
  CU_ASSERT(p->x == 3);
  CU_ASSERT(p->y == 5);
  p = p->next;
  CU_ASSERT(p->x == 0);
  CU_ASSERT(p->y == 0);

  memoryLeak_close();
}

void testCursorDeconstructor() {
  Cursor* c = newCursor();
  int i;
  for (i = 0; i < 10; cursorForward(c, i++));
  freeCursor(c);
  ASSERT_MEMORY_LEAKS();
}

void testCursorForward() {
  Cursor* c = newCursor();
  cursorLeft(c, 60);
  cursorForward(c, 100);
  ASSERT_APPROX(c->x, 50);
  ASSERT_APPROX(c->y, -86.6);
  Point* first = c->points->next;
  CU_ASSERT(first->x == 0);
  CU_ASSERT(first->y == 0);

  memoryLeak_close();
}

void testCursorLeft() {
  Cursor* c = newCursor();
  cursorLeft(c, 45);
  CU_ASSERT(c->a == 45);
  CU_ASSERT(c->x == 0);
  CU_ASSERT(c->y == 0);
  CU_ASSERT(c->points->next == NULL);

  memoryLeak_close();
}

void testCursorRight() {
  Cursor* c = newCursor();
  cursorRight(c, 45);
  CU_ASSERT(c->a == -45);
  CU_ASSERT(c->x == 0);
  CU_ASSERT(c->y == 0);
  CU_ASSERT(c->points->next == NULL);

  memoryLeak_close();
}
