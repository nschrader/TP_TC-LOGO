#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "compiler_test.h"
#include "memory_leak.h"
#include "compiler.h"
#include "instruction.h"

void testCompileParametersDeconstructor() {
  CompileParameters* p = newCompileParameters();
  void* z = malloc(sizeof(CompileParameters));
  memset(z, 0, sizeof(CompileParameters));
  CU_ASSERT(!memcmp(v, z, sizeof(CompileParameters)));

  p->svg = tmpfile();
  p->logo = tmpfile();
  p->svgPath = malloc(42);

  free(z);
  freeCompileParameters(p);
  ASSERT_MEMORY_LEAKS();
}

void testDoCompile() {
  Cursor* c = newCursor();
  Program* p = makeProgram();
  doCompile(p, c);

  Point p = c->points;
  //Count points
}
