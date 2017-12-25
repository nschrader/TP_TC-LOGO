#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "compiler.h"
#include "instruction.h"
#include "svg.h"
#include "ast.h"

static void failWithBadAstError() {
  fprintf(stderr, "Bad internal error: Inconsistent abstract syntax tree!\n");
  exit(EXIT_FAILURE);
}

static void doAtomic(const AtomicInstruction* inst, Cursor* cursor) {
  switch (inst->atomicType) {
    case LEFT: cursorLeft(cursor, inst->value); break;
    case RIGHT: cursorRight(cursor, inst->value); break;
    case FORWARD: cursorForward(cursor, inst->value); break;
    default: failWithBadAstError();
  }
}

static void doRepeat(const RepeatInstruction* inst, Cursor* cursor) {
  int i;
  for (i = 0; i < inst->value; i++) {
    doProgram(inst->program, cursor);
  }
}

void doProgram(const Program* program, Cursor* cursor) {
  if (program != NULL) {
    if (isAtomicInstruction(program->instruction)) {
      AtomicInstruction* inst = asAtomicInstruction(program->instruction);
      doAtomic(inst, cursor);
    } else if (isRepeatInstruction(program->instruction)) {
      RepeatInstruction* inst = asRepeatInstruction(program->instruction);
      doRepeat(inst, cursor);
    } else {
      failWithBadAstError();
    }
    doProgram(program->right, cursor);
  }
}

void compile(const Program* program, FILE *svg, bool niceViewBox) {
  Cursor* cursor = newCursor();
  doProgram(program, cursor);
  if (niceViewBox) {
    cursor->xOrigin -= cursor->width*0.1;
    cursor->yOrigin -= cursor->height*0.1;
    cursor->width *= 1.2;
    cursor->height *= 1.2;
  }
  writeSvg(cursor, svg);
}

void compileBare(const Program* program, FILE *svg) {
  compile(program, svg, false);
}

void compileNice(const Program* program, FILE *svg) {
  compile(program, svg, true);
}
