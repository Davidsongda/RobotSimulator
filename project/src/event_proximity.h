/**
 * @file event_proximity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_EVENT_PROXIMITY_H_
#define PROJECT_ITERATION3_SRC_EVENT_PROXIMITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "src/event_base_class.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The Proximity event class should be called when the robots_ Proximitied an obstacles.
  */
class EventProximity : public EventBaseClass {
 public:
/**
  * @brief Constructor of EventProximity.
  */
  EventProximity();

  void EmitMessage(void);

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
    * @brief Getter of Flag
    */
  bool Proximitied() { return proximitied_; }

  /**
    * @brief Setter of Flag
    */
  void Proximitied(bool p) { proximitied_ = p; }

 private:
  Position sensed_pos;
  Position sensor_pos;
  double sensor_heading_angle;
  double sensed_radius;
  bool proximitied_;
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION3_SRC_EVENT_PROXIMITY_H_ */
