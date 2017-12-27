/**
 * @file position.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_POSITION_H_
#define PROJECT_ITERATION3_SRC_POSITION_H_

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define NAMESPACE_BEGIN(name) namespace name {
#define NAMESPACE_END(name) }

// This should be placed in front of any variable defined but not used to
// satisfy the compiler - otherwise a warning is given.
#define __unused __attribute__((unused))
/**
 * @brief Recording the position by a struct.
 */
struct Position {
Position(void) : x(0.0), y(0.0) {}
Position(double in_x, double in_y) : x(in_x), y(in_y) { }
  double x;
  double y;
};

#endif  // PROJECT_ITERATION3_SRC_POSITION_H_
