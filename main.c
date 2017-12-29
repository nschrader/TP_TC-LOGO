#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "compiler.h"
#include "tc-logo.l.h"

static FILE *openInputFile(const char* path) {
  FILE* inputFile = fopen(path, "r");
  if (inputFile == NULL) {
    perror("Cannot open input file");
    exit(EXIT_FAILURE);
  }
  YY_BUFFER_STATE inputBuffer = yy_create_buffer(inputFile, YY_BUF_SIZE);
  yy_switch_to_buffer(inputBuffer);
  return inputFile;
}

static FILE *openOutputFile(const char* path) {
  return fopen(path, "w+");
}

int main() {
  Program* program;
  FILE* inputFile = openInputFile("logos/basic.logo");
  yyparse(&program);
  FILE* outputFile = openOutputFile("test123.svg");
  CompileParameters* parameters = newCompileParameters();
  parameters->hasNiceViewBox = true;
  parameters->resolution = 96;
  parameters->svg = outputFile;
  parameters->program = program;
  compile(parameters);
  free(parameters);
  fclose(inputFile);
  fclose(outputFile);
  return EXIT_SUCCESS;
}
