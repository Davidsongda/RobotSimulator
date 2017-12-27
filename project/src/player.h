/**
 * @file player.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_PLAYER_H_
#define PROJECT_ITERATION3_SRC_PLAYER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <iostream>
#include "src/motion_handler_player.h"
#include "src/player_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/sensor_proximity.h"
#include "src/sensor_distress.h"
#include "src/sensor_entity_type.h"
#include "src/player_battery.h"
#include "src/arena_mobile_entity.h"
#include "src/event_recharge.h"
#include "src/event_debattery.h"
#include "src/event_despeed.h"
#include "src/event_collision.h"
#include "src/event_distress.h"
#include "src/event_proximity.h"
#include "src/event_typeemit.h"

/*******************************************************************************
 * Namespacesplayer
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
  * @brief Create an Player. parameters is the struct which defined in player_params.
  * Player is inherited from ArenaMobileEntity.
  * @params player_params which is consisted by arena_mobile_entity_params, battery_charge_ and angle_delta.
  */
class Player : public ArenaMobileEntity {
 public:
/**
  * @brief Create an Player. parameters is the struct which defined in player_params.
  * Player is inherited from ArenaMobileEntity.
  * @params player_params which is consisted by arena_mobile_entity_params, battery_charge_ and angle_delta.
  */
  explicit Player(const struct player_params* const params);

/**
  * @brief Reset the player's battery
  */
  void ResetBattery(void);

/**
  * @brief Reset all in player.
  */
  void Reset(void);

/**
  * @brief Increased the player's heading_angle_ during its movement.
  */
  void HeadingAngleInc(void) { heading_angle_ += angle_delta_; }

/**
  * @brief Decreased the player's heading_angle_ during its movement.
  */
  void HeadingAngleDec(void) { heading_angle_ -= angle_delta_; }

/**
   * @brief Perform whatever updates are needed for player after 1
   * timestep (updating position, changing color, etc.).
   */
  void TimestepUpdate(unsigned int dt);

/**
  * @brief Handle the collision between player and others.
  *
  * @param[in] an event holding the collision.
  *
  */
  void Accept(EventCollision * e);

/**
  * @brief Handle the recharge event when the player touch the recharge_station.
  * Change battery level to max
  * @param[in] an event holding the recharge.
  *
  */
  void Accept(EventRecharge * e);

/**
  * @brief Handle the speed decreasing event when the player hit obstacles.
  * Decreased speed while player hits the obstacles
  * @param[in] an event holding the speed decreasing.
  *
  */
  void Accept(EventDespeed * e);

/**
  * @brief Handle the battery decreasing event when the player hit obstacles.
  * Decreased battery while player hits the obstacles
  * @param[in] an event holding the battery decreasing.
  *
  */
  void Accept(EventDebattery * e);

  /**
    * @brief Handle the Distress between player and others.
    */
  void Accept(EventDistressCall * e) {}

  /**
    * @brief Handle the Proximity between player and others.
    */
  void Accept(EventProximity * e) {}

  /**
    * @brief Handle the entity_type between player and others.
    */
  void Accept(EventTypeEmit * e) {}


/**
  * @brief The command event class should be called when users give a command to the view.
  */
  void EventCmd(enum event_commands cmd);

/**
  * @brief Get the current battery_level
  */
  double get_battery_level  (void) const { return battery_.get_level(); }

/**
  * @brief Get the current heading_angle
  */
  double get_heading_angle(void) const {
    return motion_handler_.get_heading_angle();
  }

/**
  * @brief Set the current heading_angle
  */
  void set_heading_angle(double ha) { motion_handler_.set_heading_angle(ha); }

/**
  * @brief Get the current speed.
  */
  double get_speed(void) { return motion_handler_.get_speed(); }

/**
  * @brief Set the current speed.
  */
  void set_speed(double sp) { motion_handler_.set_speed(sp); }

/**
  * @brief Get the player's id.
  */
  int id(void) const { return id_; }

/**
  * @brief Get the player's name.
  */
  std::string name(void) const {
    return "Player" + std::to_string(id());
  }

  /**
    * @brief set whether frezze or not.
    */
  void isFreeze(bool f) {
    isFreeze_ = f;
  }

  /**
    * @brief get whether frezze or not.
    */
  bool isFreeze() {
    return isFreeze_;
  }


 private:
  static unsigned int next_id_;

  int id_;
  double heading_angle_;
  double angle_delta_;
  PlayerBattery battery_;
  MotionHandlerPlayer motion_handler_;
  PlayerMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
  bool isFreeze_ = false;
  int clock_ = 30;
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION3_SRC_PLAYER_H_ */
