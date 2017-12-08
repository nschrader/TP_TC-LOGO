#ifndef SVG_H
#define SVG_H

#include "instruction.h"

void writeSvgDoctype(FILE* svg);
void writeSvgXml(FILE* svg);
void writeSvgTagOpen(FILE* svg);
void writeSvgTagClose(FILE* svg);
void writeSvgLine(FILE* svg, Cursor c1, Cursor c2);

#endif
