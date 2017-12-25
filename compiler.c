#include <stdio.h>
#include <stdlib.h>

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

void compile(const Program* program, FILE *svg) {
  Cursor* cursor = newCursor();
  doProgram(program, cursor);
  writeSvg(cursor, svg);
}
