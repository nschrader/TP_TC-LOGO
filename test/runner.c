#include <CUnit/Basic.h>
#include "memory_leak.h"
#include "ast_test.h"

#define ADD_TEST_TO(x, y) CU_add_test(x, #y, y)

int main() {
  CU_initialize_registry();
  CU_pSuite runner = CU_add_suite(AST_TEST_DESC, NULL, memoryLeak_close);

  ADD_TEST_TO(runner, testAtomicInstructionCast);
  ADD_TEST_TO(runner, testRepeatInstructionCast);
  ADD_TEST_TO(runner, testDeconstructors);
  ADD_TEST_TO(runner, testCostructors);

  CU_basic_run_tests();

  CU_cleanup_registry();
  return CU_get_error();
}
