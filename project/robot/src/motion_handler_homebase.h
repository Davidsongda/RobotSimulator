/**
 * @file actuator_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_MOTION_HANDLER_HOMEBASE_H_
#define PROJECT_ITERATION2_SRC_MOTION_HANDLER_HOMEBASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/robot_params.h"
#include "src/home_base_params.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"
#include "src/sensor_proximity.h"
#include "src/motion_handler.h"

class ArenaMobileEntity;
class Arena;


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief The handler for the robot's actuators, which in this case are the two
 * wheel actuators. Its main job is to translate the directional commands from
 * the user into the appropriate differential drive wheel speeds.
 *
 * MotionHandlerHomeBase manages the modification to the velocity based on
 * user input and collisions.
 * PlayerMotionBehavior translates velocity and position to a new position.
 * Both of these are straightforward, but the framework allows for more
 * sophisticated models of motion in which each wheel has distinct speed.
 *
 * For this iteration, both wheels are always going at maximum speed, and
 * cannot be controlled independently.
 */
class MotionHandlerHomeBase : public MotionHandler {
 public:
  MotionHandlerHomeBase();

  /**
   * @brief Reset the actuators to their newly constructed/un-commanded state.
   */
  void Reset(void) {
    set_speed(5);
  }

  /**
   * @brief Useless Despeed
   */
  void EventDespeed() {
    set_speed(speed_ -= 1);
  }

  /**
  * @brief Change the speed and direction according to the sensor readings.
  *
  * @param touch sensor that can be activated and contains point-of-contact.
  *
  */
  void UpdateVelocity(SensorTouch st);

  /**
   * @brief HomeBase Random change direction
   */
  void HomeBaseChangeDirection(uint dt);

  /**
   * @brief Speed Getter
   */
  double get_speed() { return speed_; }

  /**
   * @brief Speed Setter
   */
  void set_speed(double sp) {
    if (sp <= max_speed_ && sp >=0)
      speed_ = sp;
    else
      printf("invalid speed");
  }

  /**
   * @brief heading_angle_ Getter
   */
  double get_heading_angle() const { return heading_angle_;}

  /**
   * @brief heading_angle_ Setter
   */
  void set_heading_angle(double ha) { heading_angle_ = ha; }

  /**
   * @brief max_speed_ Getter
   */
  double max_speed() { return max_speed_; }

  /**
   * @brief max_speed_ Setter
   */
  void max_speed(double ms) { max_speed_ = ms; }

 private:
  double heading_angle_;
  double speed_;
  double max_speed_;
};

NAMESPACE_END(csci3081);

#endif   /* PROJECT_ITERATION2_SRC_MOTION_HANDLER_HOMEBASE_H_ */
