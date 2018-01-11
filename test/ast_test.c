#include <CUnit/Basic.h>

#include "ast_test.h"
#include "ast.h"

static Program* makeProgram() {
  Program *p, *subP;

  subP = newProgram(NULL, asInstruction(newAtomicInstruction(RIGHT, 42)));
  subP = newProgram(subP, asInstruction(newAtomicInstruction(FORWARD, 666)));

  p = newProgram(NULL, asInstruction(newAtomicInstruction(FORWARD, 1)));
  p = newProgram(p, asInstruction(newRepeatInstruction(4, subP)));
  p = newProgram(p, asInstruction(newAtomicInstruction(LEFT, 90)));

  return p;
}

void testCostructors() {
  AtomicInstruction* a;
  RepeatInstruction* r;
  Program *p, *subP;

  p = makeProgram();
  a = asAtomicInstruction(p->instruction);
  CU_ASSERT(a->atomicType == LEFT);
  CU_ASSERT(a->value == 90);

  p = p->right;
  r = asRepeatInstruction(p->instruction);
  CU_ASSERT(r->value == 4);

  subP = r->program;
  a = asAtomicInstruction(subP->instruction);
  CU_ASSERT(a->atomicType == FORWARD);
  CU_ASSERT(a->value == 666);

  subP = subP->right;
  a = asAtomicInstruction(subP->instruction);
  CU_ASSERT(a->atomicType == RIGHT);
  CU_ASSERT(a->value == 42);
  CU_ASSERT(subP->right == NULL);

  p = p->right;
  a = asAtomicInstruction(p->instruction);
  CU_ASSERT(a->atomicType == FORWARD);
  CU_ASSERT(a->value == 1);
  CU_ASSERT(p->right == NULL);
  memoryLeak_close();
}

void testDestructors() {
  Program* p = makeProgram();
  freeProgram(p);
  if (memoryLeak_close()) {
    CU_FAIL("Detected memory leek. Debug with Valgrind!");
  }
}

void testAtomicInstructionCast() {
  AtomicInstruction* a = newAtomicInstruction(FORWARD, 0);
  Instruction* i = asInstruction(a);
  CU_ASSERT(isAtomicInstruction(i));
  CU_ASSERT(!isRepeatInstruction(i));
  CU_ASSERT(a == asAtomicInstruction(i));
  memoryLeak_close();
}

void testRepeatInstructionCast() {
  RepeatInstruction* r = newRepeatInstruction(0, NULL);
  Instruction* i = asInstruction(r);
  CU_ASSERT(isRepeatInstruction(i));
  CU_ASSERT(!isAtomicInstruction(i));
  CU_ASSERT(r == asRepeatInstruction(i));
  memoryLeak_close();
}
