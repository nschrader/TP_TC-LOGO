#ifndef SVG_H
#define SVG_H

#include "instruction.h"

void writeSvgDoctype(FILE* svg);
void writeSvgXml(FILE* svg);
void writeSvgTagOpen(FILE* svg);
void writeSvgTagClose(FILE* svg);
void writeSvgLine(FILE* svg, const Cursor* c1, const Cursor* c2);

#endif
