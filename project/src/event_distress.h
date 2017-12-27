/**
 * @file event_distress.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_EVENT_DISTRESS_H_
#define PROJECT_ITERATION3_SRC_EVENT_DISTRESS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "src/event_base_class.h"
#include "src/arena_mobile_entity.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The debattery event class should be called when the mobile_entities_ hit a obstacles.
  */
class EventDistressCall : public EventBaseClass {
 public:
   /**
     * @brief Constructor of EventDistressCall.
     */
  EventDistressCall();


  void EmitMessage(void);

  /**
    * @brief Getter of Flag.
    */
  int IsDistress() { return DistressCall_; }

  /**
    * @brief Setter of Flag.
    */
  void IsDistress(int d) { DistressCall_ = d; }

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
    * @brief Getter of Flag.
    */
  bool Distressed() { return Distressed_; }

  /**
    * @brief Setter of Flag.
    */
  void Distressed(bool d) { Distressed_ = d; }



 private:
  bool Distressed_;
  Position sensed_pos;
  Position sensor_pos;
  double sensed_radius;
  int DistressCall_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_EVENT_DISTRESS_H_
