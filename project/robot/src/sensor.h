/**
 * @file sensor.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef  PROJECT_ITERATION2_SRC_SENSOR_H_
#define  PROJECT_ITERATION2_SRC_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_base_class.h"
#include "src/event_collision.h"
#include "src/event_distress.h"
#include "src/event_proximity.h"
#include "src/event_typeemit.h"

class Arena;
class ArenaMobileEntity;

// using namespace std;




/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief Base class for sensors. Should be inherited by classes like
 * SensorTouch.
 */
class Sensor {
 public:
  /**
   * @brief Constructor. Creates a deactivated sensor.
   */
  Sensor() :
  activated_(0) {}

  /**
   * @brief Default destructor.
   */
  virtual ~Sensor() = default;

  /**
   * @brief Getter method for sensor status.
   *
   * @return `true` if sensor is activated. `false` if sensor is deactivated.
   */
  int activated() const { return activated_; }

  /**
   * @brief Setter method for sensor status.
   *
   * @param value The new sensor activation status.
   */
  void activated(int value) { activated_ = value; }

  /**
   * @brief Reset the sensor to its newly constructed state.
   */
  virtual void Reset() = 0;

  /**
   * @brief Accept the event_collision.
   */
  virtual void Accept(EventCollision *const e) = 0;
  /**
   * @brief Accept the event_distress.
   */
  virtual void Accept(EventDistressCall *const e) = 0;
  /**
   * @brief Accept the event_proximity.
   */
  virtual void Accept(EventProximity *const e) = 0;
  /**
   * @brief Accept the event_typeemit.
   */
  virtual void Accept(EventTypeEmit *const e) = 0;

 private:
  int activated_;
};

NAMESPACE_END(csci3081);

#endif  //  PROJECT_ITERATION2_SRC_SENSOR_H_
