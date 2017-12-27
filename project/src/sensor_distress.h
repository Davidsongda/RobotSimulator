/**
 * @file sensor_distress.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_SENSOR_DISTRESS_H_
#define PROJECT_ITERATION3_SRC_SENSOR_DISTRESS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/event_collision.h"
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
class SensorDistress : public Sensor {
 public:
  /**
   * @brief Default constructor.
   */
  SensorDistress();

  virtual ~SensorDistress(void) {}
  /**
   * @brief Setter method for the point of contact.
   *
   * @param p The new point of contact.
   */

   /**
     * @brief Getter of range.
     */
  double range() { return range_; }

  /**
    * @brief Setter of range.
    */
  void range(double r) { range_ = r; }

  /**
    * @brief Getter of Flag.
    */
  int IsDistress() { return isDistress_; }

  /**
    * @brief Setter of Flag.
    */
  void IsDistress(int d) { isDistress_ = d; }

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
    * @brief Handle the Distress between player and others.
    */
  void Accept(EventDistressCall *const e);


  /**
   * @brief Reset the touch sensor--deactivate it.
   */
  void Reset();

  /**
    * @brief Test whether the object is inRange
    */
  bool IsRange(EventDistressCall * e);

 private:
  double range_;
  Position sensed_pos;
  Position sensor_pos;
  double sensed_radius;
  int isDistress_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_SENSOR_DISTRESS_H_
