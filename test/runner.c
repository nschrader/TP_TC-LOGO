#include <CUnit/Basic.h>

#include "memory_leak.h"
#include "ast_test.h"
#include "instruction_test.h"
#include "svg_test.h"

#define ADD_TEST_TO(x, y) CU_add_test(x, #y, y)

int main() {
  CU_initialize_registry();

  CU_pSuite ast = CU_add_suite(AST_TEST_DESC, NULL, memoryLeak_close);
  ADD_TEST_TO(ast, testAtomicInstructionCast);
  ADD_TEST_TO(ast, testRepeatInstructionCast);
  ADD_TEST_TO(ast, testDeconstructors);
  ADD_TEST_TO(ast, testCostructors);

  CU_pSuite instruction = CU_add_suite(INSTRUCTION_TEST_DESC, NULL, memoryLeak_close);
  ADD_TEST_TO(instruction, testPointDeconstructor);
  ADD_TEST_TO(instruction, testAddPoint);
  ADD_TEST_TO(instruction, testCursorDeconstructor);
  ADD_TEST_TO(instruction, testCursorForward);
  ADD_TEST_TO(instruction, testCursorLeft);
  ADD_TEST_TO(instruction, testCursorRight);

  CU_pSuite svg = CU_add_suite(SVG_TEST_DESC, NULL, memoryLeak_close);
  ADD_TEST_TO(svg, testViewPortDeconstructor);
  ADD_TEST_TO(svg, testWriteSvg);

  CU_basic_run_tests();

  CU_cleanup_registry();
  return CU_get_error();
}
