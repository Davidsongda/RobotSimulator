/**
 * @file event_typeemit.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_typeemit.h"
#include "src/arena_mobile_entity.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructor
 ******************************************************************************/
EventTypeEmit::EventTypeEmit() :
  typeemitted_(false),
  sensor_pos(0.0, 0.0),
  sensed_pos(0.0, 0.0),
  sensed_radius(0.0),
  type_(kRobot) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void EventTypeEmit::EmitMessage(void) {} /* EmitMessage() */

NAMESPACE_END(csci3081);
