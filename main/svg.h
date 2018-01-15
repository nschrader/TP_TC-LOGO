/**
 * @file
 * Write a @ref Point path to a new SVG file
 */

#ifndef SVG_H
#define SVG_H

#include "instruction.h"

/**
 * @struct ViewPort
 * Description of the SVG viewBox, width and height attributes
 *
 * @var ViewPort::xOrigin
 * The origin of x-Coordinates for viewBox
 * @var ViewPort::yOrigin
 * The origin of y-Coordinates for viewBox
 * @var ViewPort::width
 * The width of viewBox
 * @var ViewPort::height
 * The height of viewBox
 * @var ViewPort::widthIn
 * The "real world" width of SVG in Inch
 * @var ViewPort::heightIn
 * The "real world" height of SVG in Inch
 */
typedef struct {
  double xOrigin;
  double yOrigin;
  double width;
  double height;
  double widthIn;
  double heightIn;
} ViewPort;

/**
 * Constructor for @ref ViewPort.
 * All fields are zero'd
 *
 * @returns
 * A new object
 */
ViewPort* newViewPort();

/**
 * Write a @ref Point path to SVG file using a certain viewPort
 *
 * @param points
 * The path to be written
 * @param viewPort
 * The @ref ViewPort to be respected
 * @param svg
 * The file to be written to
 */
void writeSvg(const Point* points, const ViewPort* viewPort, FILE* svg);

/**
 * Deconstructor for @ref ViewPort.
 *
 * @param viewPort
 * Object to be freed
 */
void freeViewPort(ViewPort *viewPort);

#endif
