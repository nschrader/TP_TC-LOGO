/**
 * @file
 * Global definitions and configuration
 */

#ifndef MAIN_H
#define MAIN_H

/**
 * Value for no given resulution.
 * Equal to invalid infinite resolution.
 */
#define NO_RESOLUTION 0

/**
 * File name to be written to if no output file was specified by user
 */
#define STANDARD_OUTPUT_FILE "out.svg"

/**
 * Save verion of fclose() avoiding NULL-pointer errors
 */
#define closeFILE(x) {if(x != NULL) fclose(x);}

/**
 * Definition of positive-value-only type.
 * It is useful for example to prevent ambiguities between positive
 * @ref cursorLeft and negative @ref cursorRight.
 */
typedef unsigned int uint;

/**
 * Alternative declaration of main function for test purposes
 */
int main(int argc, char *argv[]);

#endif
