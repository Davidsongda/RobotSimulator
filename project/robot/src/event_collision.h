/**
 * @file event_collision.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_EVENT_COLLISION_H_
#define PROJECT_ITERATION2_SRC_EVENT_COLLISION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/event_base_class.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

 /**
  * @brief The collision event class should be called when the collision happened
  */
class EventCollision : public EventBaseClass {
 public:
  // Constructor
  EventCollision();
  void EmitMessage(void);

  /**
   * @brief Get the collided_
   */
  bool collided() { return collided_; }

  /**
   * @brief Set the collided_
   */
  void collided(bool c) { collided_ = c; }

  /**
   * @brief Get the point_of_contact
   */
  Position point_of_contact() { return point_of_contact_; }

  /**
   * @brief Set the point_of_contact
   */
  void point_of_contact(Position p) { point_of_contact_ = p; }

  /**
   * @brief Get the angle_of_contact
   */
  double angle_of_contact() { return angle_of_contact_; }

  /**
   * @brief Set the angle_of_contact
   */
  void angle_of_contact(double aoc) { angle_of_contact_ = aoc; }

 private:
  bool collided_;
  Position point_of_contact_;
  double angle_of_contact_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION2_SRC_EVENT_COLLISION_H_
