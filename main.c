#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "tc-logo.l.h"

int main() {
  Program* program;
  FILE* input = fopen("logos/basic.logo", "r");
  if (input == NULL) {
    perror("Cannot open input file");
    exit(EXIT_FAILURE);
  }
  YY_BUFFER_STATE buffer = yy_create_buffer(input, YY_BUF_SIZE);
  yyparse(&program);
  printf("Read some stuff, dunno what to do know");
  return EXIT_SUCCESS;
}
