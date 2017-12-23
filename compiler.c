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

static void doForward(Cursor* cursor, uint value, FILE* svg) {
  Cursor* new = cursorForward(cursor, value);
  writeSvgLine(svg, cursor, new);
  *cursor = *new;
}

static void doAtomic(AtomicInstruction* inst, Cursor* cursor, FILE* svg) {
  switch (inst->atomicType) {
    case LEFT: cursorLeft(cursor, inst->value); break;
    case RIGHT: cursorRight(cursor, inst->value); break;
    case FORWARD: doForward(cursor, inst->value, svg); break;
    default: failWithBadAstError();
  }
}

static void doRepeat(RepeatInstruction* inst, Cursor* cursor, FILE* svg) {
  int i;
  for (i = 0; i < inst->value; i++) {
    doProgram(inst->program, cursor, svg);
  }
}

void doProgram(Program* program, Cursor* cursor, FILE* svg) {
  if (program != NULL) {
    doProgram(program->right, cursor, svg);
    if (isAtomicInstruction(program->instruction)) {
      AtomicInstruction* inst = asAtomicInstruction(program->instruction);
      doAtomic(inst, cursor, svg);
    } else if (isRepeatInstruction(program->instruction)) {
      RepeatInstruction* inst = asRepeatInstruction(program->instruction);
      doRepeat(inst, cursor, svg);
    } else {
      failWithBadAstError();
    }
  }
}

void compile(Program* program, FILE *svg) {
  writeSvgXml(svg);
  writeSvgDoctype(svg);
  writeSvgTagOpen(svg);

  Cursor* cursor = newCursor(0, 0, 0);
  doProgram(program, cursor, svg);

  writeSvgTagClose(svg);
}
