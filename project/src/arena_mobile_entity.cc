/**
 * @file arena_mobile_entity.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_mobile_entity.h"
#include "src/player_motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

 /**
  * @brief Override the TimestepUpdate in ArenaMobileEntity. Return type is void, param is the delta time dt.
  */
void ArenaMobileEntity::TimestepUpdate(uint dt) {
  PlayerMotionBehavior h;
  h.UpdatePosition(this, dt);
} /* TimestepUpdate() */

NAMESPACE_END(csci3081);
