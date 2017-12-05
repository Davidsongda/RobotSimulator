/**
 * @file event_typeemit.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_EVENT_TYPEEMIT_H_
#define PROJECT_ITERATION2_SRC_EVENT_TYPEEMIT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "src/event_base_class.h"
#include "src/entity_type.h"

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
class EventTypeEmit : public EventBaseClass {
 public:
/**
  * @brief Constructor of EventTypeemit.
  */
  EventTypeEmit();

  void EmitMessage(void);

  /**
   * @brief Get the Sensed Position
   */
  Position SensedPos() { return sensed_pos; }

  /**
    * @brief Setter of Sensed Position.
    */
  void SensedPos(Position p) { sensed_pos = p; }

  /**
    * @brief Getter of entity
    */
  enum entity_type get_entity() { return type_; }

  /**
    * @brief Setter of entity
    */
  void set_entity(enum entity_type t) { type_ = t; }

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
    * @brief Getter of Flag
    */
  bool Typeemitted() { return typeemitted_; }

  /**
    * @brief Setter of Flag
    */
  void Typeemitted(bool t) { typeemitted_ = t; }



 private:
  bool typeemitted_;
  Position sensed_pos;
  Position sensor_pos;
  double sensed_radius;
  enum entity_type type_;
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION2_SRC_EVENT_TYPEEMIT_H_ */
