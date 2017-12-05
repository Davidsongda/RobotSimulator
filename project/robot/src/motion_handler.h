/**
 * @file actuator_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_MOTION_HANDLER_H_
#define PROJECT_ITERATION2_SRC_MOTION_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/sensor_touch.h"
#include "src/sensor_proximity.h"
#include "src/sensor_entity_type.h"
#include "src/arena_mobile_entity.h"
#include "src/arena_params.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);
class ArenaEntity;

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief The handler for the player's actuators, which in this case are the two
 * wheel actuators. Its main job is to translate the directional commands from
 * the user into the appropriate differential drive wheel speeds.
 *
 * MotionHandlerPlayer manages the modification to the velocity based on
 * user input and collisions.
 * PlayerMotionBehavior translates velocity and position to a new position.
 * Both of these are straightforward, but the framework allows for more
 * sophisticated models of motion in which each wheel has distinct speed.
 *
 * For this iteration, both wheels are always going at maximum speed, and
 * cannot be controlled independently.
 */
class MotionHandler {
 public:
  MotionHandler() {}
  /**
   * @brief Reset the actuators to their newly constructed/un-commanded state.
   */

  virtual void Reset(void) {}


  /**
  * @brief Change the speed and direction according to the sensor readings.
  *
  * @param touch sensor that can be activated and contains point-of-contact.
  *
  */
  virtual void UpdateVelocity(SensorTouch st, SensorProximity sp, SensorEntityType se) {}

  /**
   * @brief Robot Flag
   */
  virtual bool isRobot() {}

  /**
   * @brief Speed Getter
   */
  virtual double get_speed() {}

  /**
   * @brief Speed Setter
   */
  virtual void set_speed(double sp) {}

  /**
   * @brief heading_angle_ Getter
   */
  virtual double get_heading_angle() const {}

  /**
   * @brief heading_angle_ Setter
   */
  virtual void set_heading_angle(double ha) {}

  /**
   * @brief max_speed_ Getter
   */
  virtual double max_speed() {}
  /**
   * @brief max_speed_ Setter
   */
  virtual void max_speed(double ms) {}
};

NAMESPACE_END(csci3081);

#endif   /* PROJECT_ITERATION2_SRC_MOTION_HANDLER_H_ */
