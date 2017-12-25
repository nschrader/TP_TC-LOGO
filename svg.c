#include <stdio.h>

#include "svg.h"
#include "instruction.h"

#define SVG_DOCTYPE "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" " \
  "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n"
#define SVG_XML "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
#define SVG_TAG_OPEN "<svg xmlns=\"http://www.w3.org/2000/svg\" " \
  "version=\"1.1\" viewBox=\"%f %f %f %f\">\n"
#define SVG_TAG_CLOSE "</svg>\n"
#define SVG_LINE "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"red\" />\n"

static void writeSvgDoctype(FILE* svg) {
  fprintf(svg, SVG_DOCTYPE);
}

static void writeSvgXml(FILE* svg) {
  fprintf(svg, SVG_XML);
}

static void writeSvgTagOpen(const Cursor* cursor, FILE* svg) {
  fprintf(svg, SVG_TAG_OPEN, cursor->xOrigin, cursor->yOrigin,
    cursor->width, cursor->height);
}

static void writeSvgTagClose(FILE* svg) {
  fprintf(svg, SVG_TAG_CLOSE);
}

static void writeSvgLine(const Point* point, FILE* svg) {
  const Point* p1 = point;
  const Point* p2 = point->next;
  if (p2 != NULL) {
    fprintf(svg, SVG_LINE, p1->x, p1->y, p2->x, p2->y);
  }
}

void writeSvg(const Cursor* cursor, FILE* svg) {
  writeSvgXml(svg);
  writeSvgDoctype(svg);
  writeSvgTagOpen(cursor, svg);
  Point* current = cursor->points;
  while(current != NULL) {
    writeSvgLine(current, svg);
    current = current->next;
  }
  writeSvgTagClose(svg);
}
