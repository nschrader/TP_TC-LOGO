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
  FILE* logo;
  FILE* svg;
  char* svgPath;
} CompileParameters;

//For internal use only
void doProgram(const Program* program, Cursor* cursor);

CompileParameters* newCompileParameters();
void compile(const Program* program, const CompileParameters* parameters);
void freeCompileParameters(CompileParameters* compileParameters);

#endif
