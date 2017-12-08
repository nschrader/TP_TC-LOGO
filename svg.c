#include <stdio.h>

#include "svg.h"
#include "instruction.h"

#define SVG_DOCTYPE "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \
  SYSTEM \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">"
#define SVG_XML "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
#define SVG_TAG_OPEN "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"
#define SVG_TAG_CLOSE "</svg>"
#define SVG_LINE "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"red\" />"

void writeSvgDoctype(FILE* svg) {
  fprintf(svg, SVG_DOCTYPE);
}

void writeSvgXml(FILE* svg) {
  fprintf(svg, SVG_XML);
}

void writeSvgTagOpen(FILE* svg) {
  fprintf(svg, SVG_TAG_OPEN);
}

void writeSvgTagClose(FILE* svg) {
  fprintf(svg, SVG_TAG_CLOSE);
}

void writeSvgLine(FILE* svg, Cursor c1, Cursor c2) {
  fprintf(svg, SVG_LINE, c1.x, c1.y, c2.x, c2.y);
}
