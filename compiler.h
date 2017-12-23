#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include "ast.h"
#include "instruction.h"

void doProgram(Program* program, Cursor* cursor, FILE* svg);
void compile(Program* program, FILE *svg);

#endif
