/**
 * @file event_debattery.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_EVENT_DEBATTERY_H_
#define PROJECT_ITERATION3_SRC_EVENT_DEBATTERY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "src/event_base_class.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The debattery event class should be called when the mobile_entities_ hit a obstacles.
  */
class EventDebattery : public EventBaseClass {
 public:
/**
  * @brief Constructor of EventDebattery.
  */
  EventDebattery(void) {}

  /**
    * @brief EmitMessage
    */
  void EmitMessage(void) { printf("Robot Debattery!\n"); }
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION3_SRC_EVENT_DEBATTERY_H_ */
