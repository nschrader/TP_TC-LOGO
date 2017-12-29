#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdbool.h>

#include "ast.h"
#include "instruction.h"

typedef struct {
  bool hasNiceViewBox;
  int resolution;
  const Program* program;
  FILE *svg ;
} CompileParameters;

//For internal use only
void doProgram(const Program* program, Cursor* cursor);

CompileParameters* newCompileParameters();
void compile(const CompileParameters* parameters);

#endif
