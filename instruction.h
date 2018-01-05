/**
 * @file
 * Perform instructions on a cartesian coordinate system
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "main.h"

/**
 * @struct Point
 * A path made out of points in a cartesian coordinate system
 *
 * @var Point::x
 * x-Coordinate
 * @var Point::y
 * y-Coordinate
 * @var Point::next
 * Pointer to the next @ref Point in list
 */
typedef struct _Point {
  double x;
  double y;
  struct _Point *next;
} Point;

/**
 * @struct Cursor
 * Representation of a vector in a cartesian coordinate system.
 * It contains additionaly information gathered about its manipulation.
 *
 * @var Cursor::x
 * x-Coordinate
 * @var Cursor::y
 * y-Coordinate
 * @var Cursor::a
 * Angle from horizonal in trigonometrical sense (aka "Phase")
 * @var Cursor::xMin
 * Lowest x-Coordinate encountered
 * @var Cursor::yMin
 * Lowest y-Coordinate encountered
 * @var Cursor::xMax
 * Highest x-Coordinate encountered
 * @var Cursor::yMax
 * Highest y-Coordinate encountered
 * @var Cursor::points
 * A path of all previous points
 */
typedef struct {
  //Current position of the cursor
  double x;
  double y;
  int a;

  //Gathered information about the path
  double xMin;
  double yMin;
  double xMax;
  double yMax;
  Point* points;
} Cursor;

/**
 * Constructor for @ref Point
 *
 * @param x
 * Field to be set
 * @param y
 * Field to be set
 * @param next
 * Field to be set
 *
 * @returns
 * A new object
 */
Point* newPoint(double x, double y, Point* next);

/**
 * Add the curent position to the @ref Point path
 *
 * @param cursor
 * The cursor whose position should be added to its own "history"
 */
void addPoint(Cursor* cursor);

/**
 * Constructor for @ref Cursor.
 * All fields are zero'd
 *
 * @returns
 * A new object
 */
Cursor* newCursor();

/**
 * Forward cursor in current direction
 *
 * @param cursor
 * The cursor to be manipulated
 * @param value
 * The number of units it should be forwarded
 */
void cursorForward(Cursor* cursor, uint value);

/**
 * Turn cursor direction left (anti-clockwise)
 *
 * @param cursor
 * The cursor to be manipulated
 * @param value
 * The number of degrees it should be turned
 */
void cursorLeft(Cursor* cursor, uint value);

/**
 * Turn cursor direction right (clockwise)
 *
 * @param cursor
 * The cursor to be manipulated
 * @param value
 * The number of degrees it should be turned
 */
void cursorRight(Cursor* cursor, uint value);

/**
 * Destructor for @ref Cursor.
 * All attached @ref Point objects are also destructed
 *
 * @param cursor
 * Object to be freed
 */
void freeCursor(Cursor* cursor);

#endif
