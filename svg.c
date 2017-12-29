#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"
#include "instruction.h"
#include "main.h"

#define SVG_DOCTYPE "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" " \
  "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n"
#define SVG_XML "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
#define SVG_TAG_OPEN_NO_RESOLUTION "<svg xmlns=\"http://www.w3.org/2000/svg\" " \
  "version=\"1.1\" viewBox=\"%f %f %f %f\">\n"
#define SVG_TAG_OPEN "<svg xmlns=\"http://www.w3.org/2000/svg\" " \
  "version=\"1.1\" viewBox=\"%f %f %f %f\" width=\"%fin\" height=\"%fin\">\n"
#define SVG_TAG_CLOSE "</svg>\n"
#define SVG_LINE "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"red\" />\n"

ViewPort* newViewPort() {
  ViewPort* new = malloc(sizeof(ViewPort));
  memset(new, 0, sizeof(ViewPort));
  return new;
}

static void writeSvgDoctype(FILE* svg) {
  fprintf(svg, SVG_DOCTYPE);
}

static void writeSvgXml(FILE* svg) {
  fprintf(svg, SVG_XML);
}

static void writeSvgTagOpen(const ViewPort* viewPort, FILE* svg) {
  if (viewPort->widthIn == NO_RESOLUTION && viewPort->heightIn == NO_RESOLUTION) {
    fprintf(svg, SVG_TAG_OPEN_NO_RESOLUTION, viewPort->xOrigin, viewPort->yOrigin,
      viewPort->width, viewPort->height);
  } else {
    fprintf(svg, SVG_TAG_OPEN, viewPort->xOrigin, viewPort->yOrigin,
      viewPort->width, viewPort->height, viewPort->widthIn, viewPort->heightIn);
  }
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

void writeSvg(const Point* points, const ViewPort* viewPort, FILE* svg) {
  writeSvgXml(svg);
  writeSvgDoctype(svg);
  writeSvgTagOpen(viewPort, svg);
  while(points != NULL) {
    writeSvgLine(points, svg);
    points = points->next;
  }
  writeSvgTagClose(svg);
}
