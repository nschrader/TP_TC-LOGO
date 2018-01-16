/**
 * @mainpage
 * This program is a TC-LOGO compiler, a subset of the LOGO language.
 * <br>
 * It takes any TC-LOGO file as input an produces a SVG file. Some command-line
 * parameters are available, type "tlc -h" to display the help.
 * <br>
 * This package contains also several CUnit tests (see below). If you don't have
 * CUnit installed on your system, you can type `make cunit`.
 *
 * @section Make
 * To compile:
 * @code
 * make main
 * @endcode
 * To compile and run tests:
 * @code
 * make test
 * @endcode
 * To compile CUnit:
 * @code
 * make cunit
 * @endcode
 * To remove CUnit:
 * @code
 * make clean-cunit
 * @endcode
 * To generate the Doxygen documentation:
 * @code
 * make doc
 * @endcode
 * To clean-up:
 * @code
 * make clean
 * @endcode
 * To make all of them (except for cleaning-up):
 * @code
 * make all
 * @endcode
 *
 * @section program Program logic
 * This project uses Flex and Bison. To see what is behind yyparse() take a look
 * at the appropriate *.l and *.y files. The rest of the program logic can be
 * seen here:
 * @snippet main.c main
 *
 * @see ast.h
 * @see compiler.h
 * @see main.h
 * @see instruction.h
 * @see svg.h
 * @see memory_leak.h
 * @see @ref tc-logo.l
 * @see @ref tc-logo.y
 */

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "ast.h"
#include "compiler.h"
#include "tc-logo.l.h"

#define NO_MORE_OPTS -1
#define HELP_MESSAGE "%1$s - the TC-LOGO compiler\n" \
"Usage: %1$s [options] file\n" \
"Options:\n" \
"\t-h\t\t Print this help\n" \
"\t-v\t\t Make a nice viewBox (i.e. add some margin)\n" \
"\t-r resolution\t Calculate the real size of the logo\n" \
"\t\t\t using the resolution given in DPI\n"

static void printHelp(char* executable) {
  printf(HELP_MESSAGE, executable);
  exit(EXIT_SUCCESS);
}

static FILE* openInputFile(const char* path) {
  FILE* inputFile = openFILE(path, "r");
  if (inputFile == NULL) {
    perror("Cannot open input file");
    exit(EXIT_FAILURE);
  }
  YY_BUFFER_STATE inputBuffer = yy_create_buffer(inputFile, YY_BUF_SIZE);
  yy_switch_to_buffer(inputBuffer);
  return inputFile;
}

static FILE *openOutputFile(const char* path) {
  FILE* outputFile = openFILE(path, "w");
  if (outputFile == NULL) {
    outputFile = fopen(STANDARD_OUTPUT_FILE, "w");
  }
  if (outputFile == NULL) {
    perror("Cannot open output file");
    exit(EXIT_FAILURE);
  }
  return outputFile;
}

static uint getResolution(char* optarg) {
  uint value = atoi(optarg);
  if (value <= 0) {
    fprintf(stderr, "Resolution must be a positive number in DPI.\n"
    "For example, use \"-r 96\" for 96 DPI.\n");
    exit(EXIT_FAILURE);
  }
  return value;
}

void cleanUpParameters(int exitCode, void* arg) {
  CompileParameters* parameters = (CompileParameters*) arg;
  if (exitCode == EXIT_FAILURE) {
    removePath(parameters->svgPath);
  }
  yypop_buffer_state();
  freeCompileParameters(parameters);
}

static CompileParameters* getArguments(int argc, char* argv[]) {
  CompileParameters* parameters = newCompileParameters();
  char opt;
  char* inputPath;
  char* outputPath;
  on_exit(&cleanUpParameters, parameters);
  while ((opt = getopt(argc, argv, "hvr:o:")) != NO_MORE_OPTS) {
    switch (opt) {
      case 'h': printHelp(argv[0]); break;
      case 'v': parameters->hasNiceViewBox = true; break;
      case 'r': parameters->resolution = getResolution(optarg); break;
      case 'o': parameters->svgPath = optarg; break;
      default: exit(EXIT_FAILURE); break;
    }
  }
  if (optind >= argc) {
    fprintf(stderr, "Expected input file\n");
    exit(EXIT_FAILURE);
  }
  parameters->logo = openInputFile(argv[optind]);
  parameters->svg = openOutputFile(parameters->svgPath);
  return parameters;
}

//! [main]
int main(int argc, char *argv[]) {
  Program* program;
  CompileParameters* parameters = getArguments(argc, argv);
  yyparse(&program);
  compile(program, parameters);
  freeProgram(program);
  return EXIT_SUCCESS;
}
//! [main]
