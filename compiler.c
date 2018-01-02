#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"
#include "instruction.h"
#include "svg.h"
#include "ast.h"

#define ADD_MARGIN_TO_ORIGIN(origin, size) (origin - size*0.1)
#define ADD_MARGIN_TO_SIZE(size) (size * 1.2)

CompileParameters* newCompileParameters() {
  CompileParameters* new = malloc(sizeof(CompileParameters));
  memset(new, 0, sizeof(CompileParameters));
  return new;
}

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

static ViewPort* makeViewPort(const CompileParameters* parameters, const Cursor* cursor) {
  ViewPort* viewPort = newViewPort();
  double width = cursor->xMax - cursor->xMin;
  double height = cursor->yMax - cursor->yMin;
  if (parameters->hasNiceViewBox) {
    viewPort->xOrigin = ADD_MARGIN_TO_ORIGIN(cursor->xMin, width);
    viewPort->yOrigin = ADD_MARGIN_TO_ORIGIN(cursor->yMin, height);
    viewPort->width = ADD_MARGIN_TO_SIZE(width);
    viewPort->height = ADD_MARGIN_TO_SIZE(height);
  } else {
    viewPort->xOrigin = cursor->xMin;
    viewPort->yOrigin = cursor->yMin;
    viewPort->width = width;
    viewPort->height = height;
  }
  if (parameters->resolution != NO_RESOLUTION) {
    viewPort->widthIn = viewPort->width / parameters->resolution;
    viewPort->heightIn = viewPort->height / parameters->resolution;
  }
  return viewPort;
}

void compile(const Program* program, const CompileParameters* parameters) {
  Cursor* cursor = newCursor();
  doProgram(program, cursor);
  ViewPort* viewPort = makeViewPort(parameters, cursor);
  writeSvg(cursor->points, viewPort, parameters->svg);
  freeCursor(cursor);
  free(viewPort);
}

void freeCompileParameters(CompileParameters* compileParameters) {
  closeFILE(compileParameters->logo);
  closeFILE(compileParameters->svg);
  free(compileParameters);
}
