/**
 * @file
 * Compile a TC-LOGO AST to SVG
 */

#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdbool.h>

#include "ast.h"
#include "instruction.h"
#include "main.h"

/**
 * @struct CompileParameters
 * Parameters passed to @ref compile describing input file, output file and format
 *
 * @var CompileParameters::hasNiceViewBox
 * Should the compiler make a nice viewBox (ie add some margin)?
 * @var CompileParameters::resolution
 * Calculate the real size of the logo using the resolution given in DPI
 * @var CompileParameters::logo
 * Input file (so the compiler can close it in case of error)
 * @var CompileParameters::svg
 * Output file to write to
 * @var CompileParameters::svgPath
 * Path of output file (so the compiler can remove it in case of error)
 */
typedef struct {
  bool hasNiceViewBox;
  uint resolution;
  FILE* logo;
  FILE* svg;
  char* svgPath;
} CompileParameters;

/**
 * For internal use only, recursive bare compilation subroutine.
 *
 * @param program
 * The abstrct syntax tree
 * @param cursor
 * A vector to be manipulated by each instruction in the abstract syntax tree
 */
void doProgram(const Program* program, Cursor* cursor);

/**
 * Cunstructor for @ref CompileParameters structure
 *
 * @returns
 * A new and zero'd @ref CompileParameters structure
 */
CompileParameters* newCompileParameters();

/**
 * Compile the given abstrct syntax tree and write output to file
 *
 * @param program
 * The abstract syntax tree
 * @param parameters
 * The configuraton describing output file and format
 */
void compile(const Program* program, const CompileParameters* parameters);

/**
 * Deconstructor for @ref CompileParameters structure.
 * Closes all files described by FILE fields and frees structure
 *
 * @param compileParameters
 * structure to be freed
 */
void freeCompileParameters(CompileParameters* compileParameters);

#endif
