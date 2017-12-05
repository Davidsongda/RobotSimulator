/**
 * @file arena_entity_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_ARENA_ENTITY_PARAMS_H_
#define PROJECT_ITERATION2_SRC_ARENA_ENTITY_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include "src/position.h"
#include "src/color.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
/**
 * @brief ArenaEntity's params
 */
struct arena_entity_params {
  arena_entity_params(void) : radius(), pos(), color(), type() {}
  double radius;
  Position pos;
  Color color;
  enum entity_type type;
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION2_SRC_ARENA_ENTITY_PARAMS_H_ */
