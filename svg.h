#ifndef SVG_H
#define SVG_H

#include "instruction.h"

typedef struct {
  double xOrigin;
  double yOrigin;
  double width;
  double height;
  double widthIn;
  double heightIn;
} ViewPort;

ViewPort* newViewPort();
void writeSvg(const Point* points, const ViewPort* viewPort, FILE* svg);

#endif
