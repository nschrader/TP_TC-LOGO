#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdbool.h>

#include "ast.h"
#include "instruction.h"

void doProgram(const Program* program, Cursor* cursor);
void compile(const Program* program, FILE *svg, bool niceViewBox);
void compileBare(const Program* program, FILE *svg);
void compileNice(const Program* program, FILE *svg);

#endif
