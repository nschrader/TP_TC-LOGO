#include <CUnit/Basic.h>
#include "ast_test.h"

#define ADD_TEST_TO(x, y) CU_add_test(x, #y, y)

int main() {
  CU_initialize_registry();
  CU_pSuite runner = CU_add_suite(AST_TEST_DESC, NULL, NULL);

  ADD_TEST_TO(runner, testAtomicInstructionCast);
  ADD_TEST_TO(runner, testRepeatInstructionCast);

  //Try without...
  CU_basic_set_mode(CU_BRM_NORMAL);
  CU_basic_run_tests();

  CU_cleanup_registry();
  return CU_get_error();
}
