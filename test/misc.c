#include <stdio.h>

#include "memory_leak.h"
#include "misc.h"
#include "ast.h"

Program* makeProgram() {
  Program *p, *subP;

  subP = newProgram(NULL, asInstruction(newAtomicInstruction(RIGHT, 42)));
  subP = newProgram(subP, asInstruction(newAtomicInstruction(FORWARD, 666)));

  p = newProgram(NULL, asInstruction(newAtomicInstruction(FORWARD, 1)));
  p = newProgram(p, asInstruction(newRepeatInstruction(4, subP)));
  p = newProgram(p, asInstruction(newAtomicInstruction(LEFT, 90)));

  return p;
}

int countLines(FILE* f) {
  int i;
  size_t n = 0;
  char* str = NULL;
  rewind(f);

  for (i = 0; getline(&str, &n, f) != EOF; i++);
  real_free(str);
  return i;
}
