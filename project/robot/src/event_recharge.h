/**
 * @file event_recharge.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_EVENT_RECHARGE_H_
#define PROJECT_ITERATION2_SRC_EVENT_RECHARGE_H_

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
  * @brief The recharge event class should be called when robot hit the recharge_station.
  */
class EventRecharge : public EventBaseClass {
 public:
   /**
     * @brief Constructor of EventRecharge.
     */
  EventRecharge(void) {}

  void EmitMessage(void) { printf("Robot Battery recharged!\n"); }
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION2_SRC_EVENT_RECHARGE_H_ */
