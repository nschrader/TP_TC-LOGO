#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "svg_test.h"
#include "memory_leak.h"
#include "svg.h"

static int countLines(FILE* f) {
  int i;
  size_t n = 0;
  char* str = NULL;
  rewind(f);

  for (i = 0; getline(&str, &n, f) != EOF; i++);
  real_free(str);
  return i;
}

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
