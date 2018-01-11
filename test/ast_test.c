#include <CUnit/Basic.h>

#include "ast_test.h"
#include "ast.h"

void testAtomicInstructionCast() {
  AtomicInstruction* a = newAtomicInstruction(FORWARD, 0);
  Instruction* i = asInstruction(a);
  CU_ASSERT(isAtomicInstruction(i));
  CU_ASSERT(!isRepeatInstruction(i));
  CU_ASSERT(a == asAtomicInstruction(i));
}

void testRepeatInstructionCast() {
  RepeatInstruction* r = newRepeatInstruction(0, NULL);
  Instruction* i = asInstruction(r);
  CU_ASSERT(isRepeatInstruction(i));
  CU_ASSERT(!isAtomicInstruction(i));
  CU_ASSERT(r == asRepeatInstruction(i));
}
