/**
 * @file mobile_arena_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_ARENA_MOBILE_ENTITY_H_
#define PROJECT_ITERATION1_SRC_ARENA_MOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include "src/arena_entity.h"
#include "src/event_base_class.h"
#include "src/event_recharge.h"
#include "src/event_despeed.h"
#include "src/event_debattery.h"
#include "src/event_collision.h"
#include "src/color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
  * @brief Create an ArenaMobileEntity. parameters are radius, collisiton_Delta, position and color.
  * ArenaMobileEntity is inherited from ArenaEntity.
  */
class ArenaMobileEntity : public ArenaEntity {
 public:
/**
  * @brief Create an ArenaMobileEntity. parameters are radius, collisiton_Delta, position and color.
  * ArenaMobileEntity is inherited from ArenaEntity.
  */
  ArenaMobileEntity(double radius, double collision_delta,
                    const Position& pos, const Color& color) :
      ArenaEntity(radius, pos, color),
      collision_delta_(collision_delta) {}

/**
  * @brief Shows that the ArenaMobileEntity is a mobile entity.
  * Return type is bool
  */
  bool is_mobile(void) { return true; }

  /**
   * @brief Create the Getter of heading_angle to a pure virtual function.
   * Heading_angle is the direction of the mobile_entities_'s movement
   * Return type is double.
   */
  virtual double heading_angle(void) const = 0;

  /**
   * @brief Create the Setter of heading_angle to a pure virtual function.
   * Heading_angle is the direction of the mobile_entities_'s movement
   * param[in] double.
   */
  virtual void heading_angle(double heading_angle) = 0;

  /**
   * @brief Create the Getter of speed to a pure virtual function.
   * Speed is the speed of the mobile_entities_
   * Return type is double.
   */
  virtual double speed(void) = 0;

  /**
   * @brief Create the Setter of speed to a pure virtual function.
   * Speed is the speed of the mobile_entities_
   * param[in] double.
   */
  virtual void speed(double sp) = 0;

  /**
   * @brief Create the Getter of collision_delta.
   * collision_delta is the buffer distance of collisions.
   * Return type is double.
   */
  double collision_delta(void) const { return collision_delta_; }

  /**
   * @brief Override the TimestepUpdate in ArenaMobileEntity.
   * Return type is void
   * param[in] delta time dt.
   */
  void TimestepUpdate(uint dt);

  /**
  * @brief Handle the collision between arena_mobile_entity and others.
  *
  * @param[in] an event holding the collision.
  *
  */
  virtual void Accept(EventCollision * e) = 0;

  /**
  * @brief Handle the recharge event when the mobile_entities_ touch the recharge_station.
  *
  * @param[in] an event holding the recharge.
  *
  */
  virtual void Accept(EventRecharge * e) = 0;

  /**
  * @brief Handle the speed decreasing event when the mobile_entities_ hit obstacles.
  *
  * @param[in] an event holding the speed decreasing.
  *
  */
  virtual void Accept(EventDespeed * e) = 0;

  /**
  * @brief Handle the battery decreasing event when the mobile_entities_ hit obstacles.
  *
  * @param[in] an event holding the battery decreasing.
  *
  */
  virtual void Accept(EventDebattery * e) = 0;

 private:
  double collision_delta_;
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION1_SRC_ARENA_MOBILE_ENTITY_H_ */
