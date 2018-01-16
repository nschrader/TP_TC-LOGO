#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "svg_test.h"
#include "memory_leak.h"
#include "svg.h"
#include "misc.h"

void testViewPortDeconstructor() {
  ViewPort* v = newViewPort();
  void* z = malloc(sizeof(ViewPort));
  memset(z, 0, sizeof(ViewPort));
  CU_ASSERT(!memcmp(v, z, sizeof(ViewPort)));

  free(z);
  freeViewPort(v);
  ASSERT_MEMORY_LEAKS();
}

void testWriteSvg() {
  FILE* tmp = tmpfile();
  ViewPort* v = newViewPort();
  Point* p;
  p = newPoint(0, 0, NULL);
  p = newPoint(1, 2, p);
  p = newPoint(3, 4, p);

  writeSvg(p, v, tmp);
  CU_ASSERT(countLines(tmp) == 6);

  fclose(tmp);
  memoryLeak_close();
}
