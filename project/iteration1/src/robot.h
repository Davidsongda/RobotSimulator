/**
 * @file robot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_ROBOT_H_
#define PROJECT_ITERATION1_SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <iostream>
#include "src/robot_motion_handler.h"
#include "src/robot_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/robot_battery.h"
#include "src/arena_mobile_entity.h"
#include "src/event_recharge.h"
#include "src/event_debattery.h"
#include "src/event_despeed.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
  * @brief Create an Robot. parameters is the struct which defined in robot_params.
  * Robot is inherited from ArenaMobileEntity.
  * @params robot_params which is consisted by arena_mobile_entity_params, battery_charge_ and angle_delta.
  */
class Robot : public ArenaMobileEntity {
 public:
/**
  * @brief Create an Robot. parameters is the struct which defined in robot_params.
  * Robot is inherited from ArenaMobileEntity.
  * @params robot_params which is consisted by arena_mobile_entity_params, battery_charge_ and angle_delta.
  */
  explicit Robot(const struct robot_params* const params);

/**
  * @brief Reset the robot's battery
  */
  void ResetBattery(void);

/**
  * @brief Reset all in robot.
  */
  void Reset(void);

/**
  * @brief Increased the robot's heading_angle_ during its movement.
  */
  void HeadingAngleInc(void) { heading_angle_ += angle_delta_; }

/**
  * @brief Decreased the robot's heading_angle_ during its movement.
  */
  void HeadingAngleDec(void) { heading_angle_ -= angle_delta_; }

/**
   * @brief Perform whatever updates are needed for robot after 1
   * timestep (updating position, changing color, etc.).
   */
  void TimestepUpdate(unsigned int dt);
/**
  * @brief Handle the collision between robot and others.
  *
  * @param[in] an event holding the collision.
  *
  */
  void Accept(EventCollision * e);

/**
  * @brief Handle the recharge event when the robot touch the recharge_station.
  * Change battery level to max
  * @param[in] an event holding the recharge.
  *
  */
  void Accept(EventRecharge * e);

/**
  * @brief Handle the speed decreasing event when the robot hit obstacles.
  * Decreased speed while robot hits the obstacles
  * @param[in] an event holding the speed decreasing.
  *
  */
  void Accept(EventDespeed * e);

/**
  * @brief Handle the battery decreasing event when the robot hit obstacles.
  * Decreased battery while robot hits the obstacles
  * @param[in] an event holding the battery decreasing.
  *
  */
  void Accept(EventDebattery * e);

/**
  * @brief The command event class should be called when users give a command to the view.
  */
  void EventCmd(enum event_commands cmd);

/**
  * @brief Get the current battery_level
  */
  double battery_level  (void) const { return battery_.level(); }

/**
  * @brief Get the current heading_angle
  */
  double heading_angle(void) const { return motion_handler_.heading_angle(); }

/**
  * @brief Set the current heading_angle
  */
  void heading_angle(double ha) { motion_handler_.heading_angle(ha); }

/**
  * @brief Get the current speed.
  */
  double speed(void) { return motion_handler_.speed(); }

/**
  * @brief Set the current speed.
  */
  void speed(double sp) { motion_handler_.speed(sp); }

/**
  * @brief Get the robot's id.
  */
  int id(void) const { return id_; }

/**
  * @brief Get the robot's name.
  */
  std::string name(void) const {
    return "Robot" + std::to_string(id());
  }

 private:
  static unsigned int next_id_;

  int id_;
  double heading_angle_;
  double angle_delta_;
  RobotBattery battery_;
  RobotMotionHandler motion_handler_;
  RobotMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION1_SRC_ROBOT_H_ */
