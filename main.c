#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "tc-logo.l.h"

int main() {
  Program* program;
  FILE* inputFile = fopen("logos/basic.logo", "r");
  if (inputFile == NULL) {
    perror("Cannot open input file");
    exit(EXIT_FAILURE);
  }
  YY_BUFFER_STATE inputBuffer = yy_create_buffer(inputFile, YY_BUF_SIZE);
  yy_switch_to_buffer(inputBuffer);
  yyparse(&program);
  printf("Read some stuff, dunno what to do now\n");
  return EXIT_SUCCESS;
}
