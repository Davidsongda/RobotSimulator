/**
 * @file arena_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 *
 */

#ifndef PROJECT_ITERATION1_SRC_ARENA_PARAMS_H_
#define PROJECT_ITERATION1_SRC_ARENA_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_params.h"
#include "src/home_base_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constant Definitions
 ******************************************************************************/
#define MAX_OBSTACLES 8

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
/**
 * @brief Arena's params
 */
struct arena_params {
  // Entities populating the arena
  struct robot_params robot;
  struct arena_entity_params recharge_station;
  struct home_base_params home_base;
  struct arena_entity_params obstacles[MAX_OBSTACLES];
  // Dimensions of graphics window inside which robots must operate
  size_t n_obstacles;
  uint x_dim;
  uint y_dim;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION1_SRC_ARENA_PARAMS_H_
