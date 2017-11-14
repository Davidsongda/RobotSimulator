/**
 * @file event_despeed.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_EVENT_DESPEED_H_
#define PROJECT_ITERATION1_SRC_EVENT_DESPEED_H_

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
class EventDespeed: public EventBaseClass {
 public:
   /**
     * @brief Constructor of EventDespeed.
     */
  EventDespeed(void) {}

  void EmitMessage(void) { printf("Robot Despeed!\n"); }
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION1_SRC_EVENT_DESPEED_H_ */
