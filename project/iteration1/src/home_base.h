
/**
 * @file home_base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_HOME_BASE_H_
#define PROJECT_ITERATION1_SRC_HOME_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/robot_motion_handler.h"
#include "src/robot_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/arena_mobile_entity.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
  * @brief Create an HomeBase. parameters is the struct which defined in home_base_params.
  * HomeBase is inherited from ArenaMobileEntity.
  * @params home_base_params which is consisted by arena_mobile_entity_params and angle_delta.
  */
class HomeBase : public ArenaMobileEntity {
 public:
  /**
    * @brief Create an HomeBase. parameters is the struct which defined in home_base_params.
    * HomeBase is inherited from ArenaMobileEntity.
    * @params home_base_params which is consisted by arena_mobile_entity_params and angle_delta.
    */
  explicit HomeBase(const struct home_base_params* const params);

  // Reset all in the arena
  void Reset(void);

/**
  * @brief Increased the heading_angle by adding angle_delta_ to the heading_angle
  */
  void HeadingAngleInc(void) { heading_angle_ += angle_delta_; }

/**
  * @brief Decreased the heading_angle by submitting angle_delta_ from the heading_angle
  */
  void HeadingAngleDec(void) { heading_angle_ -= angle_delta_; }

/**
   * @brief Override the TimestepUpdate in HomeBase.
   * Return type is void
   * param[in] delta time dt.
   */
  void TimestepUpdate(unsigned int dt);

/**
  * @brief Handle the collision between homebase and others.
  *
  * @param[in] an event holding the collision.
  *
  */
  void Accept(EventCollision * e);
/**
  * @brief Handle the recharge event when the homebase touch the recharge_station.
  * But we do not actually write anything in there because homebase does not have battery.
  * @param[in] an event holding the recharge.
  *
  */
  void Accept(EventRecharge * e);

/**
  * @brief Handle the speed decreasing event when the homebase hit obstacles.
  * But we do not actually write anything in there because homebase would not decrase speed after hit obstacles.
  * @param[in] an event holding the speed decreasing.
  *
  */
  void Accept(EventDespeed * e);

/**
  * @brief Handle the battery decreasing event when the homebase hit obstacles.
  * But we do not actually write anything in there because homebase does not have battery.
  * @param[in] an event holding the battery decreasing.
  *
  */
  void Accept(EventDebattery * e);

/**
  * @brief The command event class should be called when users give a command to the view.
  */
  void EventCmd(enum event_commands cmd);

/**
  * @brief Get the heading_angle of home
  */
  double heading_angle(void) const { return motion_handler_.heading_angle(); }
/**
  * @brief Set the heading_angle of home
  */
  void heading_angle(double ha) { motion_handler_.heading_angle(ha); }

/**
  * @brief Get the speed of home
  */
  double speed(void) { return motion_handler_.speed(); }

/**
  * @brief Set the speed of home
  */
  void speed(double sp) { motion_handler_.speed(sp); }

/**
  * @brief Get the id of home
  */
  int id(void) const { return id_; }

/**
  * @brief Get the name of home
  */
  std::string name(void) const {
    return "Home Base" + std::to_string(id());
  }


 private:
  static unsigned int next_id_;

  int id_;
  double heading_angle_;
  double angle_delta_;
  RobotMotionHandler motion_handler_;
  RobotMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION1_SRC_HOME_BASE_H_
