/**
 * @file actuator_cmd_event.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_EVENT_COMMAND_H_
#define PROJECT_ITERATION1_SRC_EVENT_COMMAND_H_

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
  * @brief The command event class should be called when users give a command to the view.
  */
class EventCommand : public EventBaseClass {
 public:
   /**
    * @brief Create EventCommand as a Constructor.
    */
  explicit EventCommand(enum event_commands cmd) : cmd_(cmd) {}

  void EmitMessage(void) { printf("Motion cmd %d received\n", cmd_); }

  /**
   * @brief Get the command from user.
   */
  enum event_commands cmd(void) const { return cmd_; }

 private:
  enum event_commands cmd_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION1_SRC_EVENT_COMMAND_H_
