#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "compiler_test.h"
#include "memory_leak.h"
#include "compiler.h"
#include "instruction.h"
#include "misc.h"

void testCompileParametersDeconstructor() {
  CompileParameters* p = newCompileParameters();
  void* z = malloc(sizeof(CompileParameters));
  memset(z, 0, sizeof(CompileParameters));
  CU_ASSERT(!memcmp(p, z, sizeof(CompileParameters)));

  p->svg = tmpfile();
  p->logo = tmpfile();

  free(z);
  freeCompileParameters(p);
  ASSERT_MEMORY_LEAKS();
}

void testDoProgram() {
  Cursor* c = newCursor();
  Program* program = makeProgram();
  doProgram(program, c);

  Point* p = c->points;
  int nPoints;
  for(nPoints = 0; (p=p->next) != NULL; nPoints++);
  CU_ASSERT(nPoints == 5)

  memoryLeak_close();
}

void testCompile() {
  Program* program = makeProgram();
  CompileParameters* p = newCompileParameters();

  p->svg = tmpfile();
  compile(program, p);
  fseek(p->svg, 0L, SEEK_END);
  CU_ASSERT(ftell(p->svg) > 0);

  freeProgram(program);
  freeCompileParameters(p);
  ASSERT_MEMORY_LEAKS();
}
