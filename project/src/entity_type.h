/**
 * @file actuator_entity_type.h
 *
 * @copyright 2017 John Harwell, All rights reserved.
 *
 */

#ifndef PROJECT_ITERATION3_SRC_ENTITY_TYPE_H_
#define PROJECT_ITERATION3_SRC_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/

 /**
  * @brief The enumeration of eneities
  */
enum entity_type {
  kRobot = 0,
  kSuperBot,  // 1
  kPlayer,  // 2
  kHomeBase,  // 3
  kRechargeStation,  // 4
  kObstacles  // 5
};
NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_ENTITY_TYPE_H_
