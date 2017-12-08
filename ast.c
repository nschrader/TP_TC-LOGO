#include <stdlib.h>

#include "ast.h"

Program* newProgram(Program* right, Instruction* instruction) {
  Program* new = malloc(sizeof(Program));
  new->right = right;
  new->instruction = instruction;
  return new;
}

AtomicInstruction* newAtomicInstruction(AtomicInstructionType atomicType, int value) {
  AtomicInstruction* new = malloc(sizeof(AtomicInstruction));
  new->type = ATOMIC;
  new->atomicType = atomicType;
  new->value = value;
  return new;
}

RepeatInstruction* newRepeatInstruction(int value, Program* program) {
  RepeatInstruction* new = malloc(sizeof(RepeatInstruction));
  new->type = REPEAT;
  new->value = value;
  new->program = program;
  return new;
}
