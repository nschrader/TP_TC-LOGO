#ifndef MAIN_H
#define MAIN_H

#define NO_RESOLUTION 0
#define STANDARD_OUTPUT_FILE "out.svg"
#define closeFILE(x) {if(x != NULL) fclose(x);}

typedef unsigned int uint;

int main(int argc, char *argv[]);

#endif
