#include <stdlib.h>
#include "ast.h"

#ifdef TEST_CASE
#include "memory_leak.h"
#endif

Program* newProgram(Program* right, Instruction* instruction) {
  Program* new = malloc(sizeof(Program));
  new->right = right;
  new->instruction = instruction;
  return new;
}

void freeProgram(Program* program) {
  if (program->right != NULL) {
    freeProgram(program->right);
  }
  freeInstruction(program->instruction);
  free(program);
}

AtomicInstruction* newAtomicInstruction(AtomicInstructionType atomicType, uint value) {
  AtomicInstruction* new = malloc(sizeof(AtomicInstruction));
  new->type = ATOMIC;
  new->atomicType = atomicType;
  new->value = value;
  return new;
}

void freeAtomicInstruction(AtomicInstruction* atomicInstruction) {
  free(atomicInstruction);
}

RepeatInstruction* newRepeatInstruction(uint value, Program* program) {
  RepeatInstruction* new = malloc(sizeof(RepeatInstruction));
  new->type = REPEAT;
  new->value = value;
  new->program = program;
  return new;
}

void freeRepeatInstruction(RepeatInstruction* repeatInstruction) {
  freeProgram(repeatInstruction->program);
  free(repeatInstruction);
}

void freeInstruction(Instruction* instruction) {
  if (isAtomicInstruction(instruction)) {
    freeAtomicInstruction(asAtomicInstruction(instruction));
  } else if (isRepeatInstruction(instruction)) {
    freeRepeatInstruction(asRepeatInstruction(instruction));
  } else {
    free(instruction);
  }
}
