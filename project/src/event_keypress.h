/**
 * @file event_keypress.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_EVENT_KEYPRESS_H_
#define PROJECT_ITERATION3_SRC_EVENT_KEYPRESS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "src/event_base_class.h"
#include "src/event_commands.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The keypress event class should be called when the pressed a key.
  */
class EventKeypress : public EventBaseClass {
 public:
   /**
     * @brief Constructor of EventKeypress.
     */
  explicit EventKeypress(int key) : key_(key) {}


  /**
    * @brief EmitMessage
    */
  void EmitMessage(void) { printf("Keypress command received\n"); }

  /**
   * @brief Get the key which user pressed.
   */
  int get_key(void) const {return key_;}

  /**
   * @brief Constraint the command from user. Event only process up, down, left, right. Others are illegel.
   */
  enum event_commands get_key_cmd() const;

 private:
  int key_;

  EventKeypress& operator=(const EventKeypress& other) = delete;
  EventKeypress(const EventKeypress& other) = delete;
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION3_SRC_EVENT_KEYPRESS_H_ */
