#ifndef MISC_H
#define MISC_H

#include <CUnit/Basic.h>
#include "ast.h"

#define ASSERT_APPROX(x, y) CU_ASSERT((x) < (y)+.1 && (x) > (y)-.1)

Program* makeProgram();
int countLines(FILE* f);

#endif
