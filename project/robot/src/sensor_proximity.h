/**
 * @file sensor_proximity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef  PROJECT_ITERATION2_SRC_SENSOR_PROXIMITY_H_
#define  PROJECT_ITERATION2_SRC_SENSOR_PROXIMITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <math.h>
#include <vector>
#include <utility>
#include "src/range.h"
#include "src/event_proximity.h"
#include "src/sensor.h"
#include "src/position.h"
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
class SensorProximity : public Sensor {
 public:
  /**
   * @brief Default constructor.
   */
  SensorProximity();

  /**
    * @brief Getter of fv
    */
  void filed_of_view(double fv) {
     filed_of_view_ = fv;
  }

  /**
    * @brief Setter of fv
    */
  double filed_of_view() {
     return filed_of_view_;
  }

  /**
    * @brief Getter of distance
    */
  void distance(double dist) {
     distance_ = dist;
  }

  /**
    * @brief Setter of distance
    */
  double distance() {
     return distance_;
  }

  /**
    * @brief Getter of Sensed Position.
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
    * @brief Getter of Sensor HeadingAngle.
    */
  double SensorHd() { return sensor_heading_angle; }

  /**
    * @brief Setter of Sensor HeadingAngle.
    */
  void SensorHd(double hd) {sensor_heading_angle = hd; }

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
    * @brief Compute a new reading based on a proximity event.
    *
    * Note that collision events can report "no proximity" which
    * will deactivate the sensor.
    */
  void Accept(EventProximity *const e);

  /**
    * @brief Handle the entity_type between player and others.
    */
  void Accept(EventTypeEmit *const e) {}

  /**
   * @brief InRange
   */
  bool InRange(Range r1, Range r2);

   /**
    * @brief SensorReading
    */
  double SensorReading(EventProximity * e);

  /**
   * @brief Reset the touch sensor--deactivate it.
   */
  void Reset();

  double Positive(double a) {
    if (a < 0) {
      return 360 + a;
    }
    if (a > 360) {
      return fmod(a, 360);
    }
    return a;
  }

 private:
  double filed_of_view_;
  double distance_;
  Position sensed_pos;
  Position sensor_pos;
  double sensor_heading_angle;
  double sensed_radius;
};

NAMESPACE_END(csci3081);

#endif  //  PROJECT_ITERATION2_SRC_SENSOR_PROXIMITY_H_
