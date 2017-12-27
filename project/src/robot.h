
/**
 * @file robot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_ROBOT_H_
#define PROJECT_ITERATION3_SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/motion_handler_robot.h"
#include "src/motion_handler_superbot.h"
#include "src/player_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/sensor_proximity.h"
#include "src/sensor_distress.h"
#include "src/sensor_entity_type.h"
#include "src/arena_mobile_entity.h"
#include "src/event_collision.h"
#include "src/event_distress.h"
#include "src/event_typeemit.h"
#include "src/event_proximity.h"
#include "src/event_transbot.h"

class ArenaMobileEntity;
class Arena;

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/


/**
  * @brief Create an Robot. parameters is the struct which defined in home_base_params.
  * Robot is inherited from ArenaMobileEntity.
  * @params home_base_params which is consisted by arena_mobile_entity_params and angle_delta.
  */
class Robot : public ArenaMobileEntity {
 public:
  /**
    * @brief Create an Robot. parameters is the struct which defined in home_base_params.
    * Robot is inherited from ArenaMobileEntity.
    * @params home_base_params which is consisted by arena_mobile_entity_params and angle_delta.
    */
  explicit Robot(const struct robot_params* const params);

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
   * @brief Override the TimestepUpdate in Robot.
   * Return type is void
   * param[in] delta time dt.
   */
  void TimestepUpdate(unsigned int dt);

  /**
    * @brief Handle the Proximity between player and others.
    */
  void Accept(EventProximity * e);

  /**
    * @brief Handle the Distress between player and others.
    */
  void Accept(EventDistressCall * e);

  /**
    * @brief Handle the entity_type between player and others.
    */
  void Accept(EventTypeEmit * e);

  /**
    * @brief Handle the collision between player and others.
    *
    * @param[in] an event holding the collision.
    *
    */
  void Accept(EventCollision * e);

  /**
    * @brief Handle the Robot and SuperBot convert.
    */
  void Accept(EventTrans * e);

  /**
    * @brief Handle the recharge event when the player touch the recharge_station.
    * Change battery level to max
    * @param[in] an event holding the recharge.
    *
    */
    void Accept(EventRecharge * e) {}

  /**
    * @brief Handle the speed decreasing event when the player hit obstacles.
    * Decreased speed while player hits the obstacles
    * @param[in] an event holding the speed decreasing.
    *
    */
    void Accept(EventDespeed * e) {}

  /**
    * @brief Handle the battery decreasing event when the player hit obstacles.
    * Decreased battery while player hits the obstacles
    * @param[in] an event holding the battery decreasing.
    *
    */
    void Accept(EventDebattery * e) {}

/**
  * @brief Get the heading_angle of home
  */
  double get_heading_angle(void) const {
    return motion_handler_->get_heading_angle();
  }
/**
  * @brief Set the heading_angle of home
  */
  void set_heading_angle(double ha) { motion_handler_->set_heading_angle(ha); }

/**
  * @brief Get the speed of home
  */
  double get_speed(void) { return motion_handler_->get_speed(); }

/**
  * @brief Set the speed of home
  */
  void set_speed(double s) { motion_handler_->set_speed(s); }

/**
  * @brief Get the id of home
  */
  int id(void) const { return id_; }

/**
  * @brief Get the name of home
  */
  std::string name(void) const {
    return "Robot" + std::to_string(id());
  }

  /**
    * @brief is or is not robot
    */
  bool isRobot();

  /**
    * @brief Get the sensor_proximity_ activated
    */
  bool get_sp() {
    return sensor_proximity_.activated();
  }

  SensorDistress get_sensor_dis() {
    return sensor_distress_;;
  }

  SensorEntityType get_sensor_ent() {
    return sensor_entity_type_;
  }

  /**
    * @brief Get the sensor_proximity_
    */
  SensorProximity get_proximity() const {
    return sensor_proximity_;
  }

  /**
    * @brief Get the sensor_distress_
    */
  int get_sd() {
    return sensor_distress_.IsDistress();
  }

  /**
    * @brief Get the IsDistress
    */
  int IsDistress() {
    return sensor_distress_.IsDistress();
  }

  /**
    * @brief Set the IsDistress
    */
  void set_sd(int i) {
    sensor_distress_.IsDistress(i);
  }

  /**
    * @brief Get the sensor_entity_type_ activated
    */
  enum entity_type get_et() {
    return sensor_entity_type_.get_entity();
  }

  /**
    * @brief Set the Distress open or close
    */
  void get_distress() {
    if (get_speed() == 0) {
      sensor_distress_.IsDistress(0);
    } else {
      sensor_distress_.IsDistress(1);
    }
  }

  /**
    * @brief Close all sensors to ufreeze robot and avoid hit player and homebase
    */
  void closeSensors() {
    sensor_entity_type_.activated(0);
    sensor_proximity_.activated(0);
    sensor_distress_.activated(0);
  }



 private:
  static unsigned int next_id_;

  int id_;
  double heading_angle_;
  double angle_delta_;
  MotionHandler *motion_handler_;
  PlayerMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
  SensorProximity sensor_proximity_;
  SensorDistress sensor_distress_;
  SensorEntityType sensor_entity_type_;
  Position resetPos;
  double resetHd;
};



NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_ROBOT_H_
