/**
 * @file event_recharge.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_EVENT_TRANSBOT_H_
#define PROJECT_ITERATION3_SRC_EVENT_TRANSBOT_H_

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
class EventTrans : public EventBaseClass {
 public:
 /**
   * @brief Constructor of EventTrans
   */
  EventTrans(void) {}

  /**
    * @brief Setter of Trans
    */
  void Trans(bool t) {
    trans_ = t;
  }

  /**
    * @brief Getter of Trans
    */
  bool Trans() {
    return trans_;
  }
 private:
  bool trans_;

  void EmitMessage(void) { printf("Robot Transfer!\n"); }
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION3_SRC_EVENT_TRANSBOT_H_ */
