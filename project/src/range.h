/**
 * @file range.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_RANGE_H_
#define PROJECT_ITERATION3_SRC_RANGE_H_

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define NAMESPACE_BEGIN(name) namespace name {
#define NAMESPACE_END(name) }

// This should be placed in front of any variable defined but not used to
// satisfy the compiler - otherwise a warning is given.
#define __unused __attribute__((unused))
/**
 * @brief Recording the range by a struct.
 */
struct Range {
Range(void) : upper(0.0), lower(0.0) {}
Range(double in_lower, double in_upper) : lower(in_lower), upper(in_upper) { }
  double lower;
  double upper;
};

#endif  // PROJECT_ITERATION3_SRC_RANGE_H_
