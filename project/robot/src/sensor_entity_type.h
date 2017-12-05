/**
 * @file sensor_entity_type.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef  PROJECT_ITERATION2_SRC_SENSOR_ENTITY_TYPE_H_
#define  PROJECT_ITERATION2_SRC_SENSOR_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/event_typeemit.h"
#include "src/sensor.h"
#include "src/position.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief Class representing a touch sensor.
 *
 * Touch or "bump" sensors are "active" when pressed. For our purposes, imagine
 * a series of bump sensors around the perimeter of the Robot. A collision will
 * activate the sensor at a particular point of contact, which translates to an
 * angle of contact.
 */
class SensorEntityType : public Sensor {
 public:
  /**
   * @brief Default constructor.
   */
  SensorEntityType();


/**
 * @brief Compute a new reading based on a collision event.
 *
 * Note that collision events can report "no collision" which
 * will deactivate the sensor.
 */
  void Accept(EventCollision *const e) {}

  /**
    * @brief Handle the Distress between player and others.
    */
  void Accept(EventDistressCall *const e) {}

  /**
    * @brief Handle the Proximity between player and others.
    */
  void Accept(EventProximity *const e) {}

  /**
    * @brief Handle the entity_type between player and others.
    */
  void Accept(EventTypeEmit *const e);

/**
 * @brief Reset the touch sensor--deactivate it.
 */
  void Reset() override;

  /**
    * @brief Getter of range.
    */
  double range() { return range_; }

  /**
    * @brief Setter of range.
    */
  void range(double r) { range_ = r; }

  /**
    * @brief Getter of entity
    */
  enum entity_type get_entity() { return s_entity_; }

  /**
    * @brief Setter of entity
    */
  void set_entity(enum entity_type t) { s_entity_ = t; }

  /**
   * @brief Get the Sensed Position
   */
  Position SensedPos() { return sensed_pos; }

  /**
    * @brief Setter of Sensed Position.
    */
  void SensedPos(Position p) { sensed_pos = p; }

  /**
    * @brief Getter of Sensor Position.
    */
  Position SensorPos() { return sensor_pos; }

  /**
    * @brief Setter of Sensor Position.
    */
  void SensorPos(Position p) { sensor_pos = p; }

  /**
    * @brief Getter of Sensor radius.
    */
  double SensedRad() { return sensed_radius; }

  /**
    * @brief Setter of Sensor radius.
    */
  void SensedRad(double rad) { sensed_radius = rad; }

  /**
    * @brief Test whether the object is inRange
    */
  bool InRange(EventTypeEmit * e);



 private:
  double range_;
  Position sensed_pos;
  Position sensor_pos;
  double sensed_radius;
  enum entity_type s_entity_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION2_SRC_SENSOR_ENTITY_TYPE_H_
