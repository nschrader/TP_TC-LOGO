#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdbool.h>

#include "ast.h"
#include "instruction.h"
#include "main.h"

typedef struct {
  bool hasNiceViewBox;
  uint resolution;
  const Program* program;
  FILE *svg ;
} CompileParameters;

//For internal use only
void doProgram(const Program* program, Cursor* cursor);

CompileParameters* newCompileParameters();
void compile(const CompileParameters* parameters);

#endif
