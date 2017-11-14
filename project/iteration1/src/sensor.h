/**
 * @file sensor.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_SENSOR_H_
#define PROJECT_ITERATION1_SRC_SENSOR_H_

NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Includes
 ******************************************************************************/
/**
  * @brief The sensor event class from which all sensors should derive from..
  */
class Sensor{
 public:
  virtual ~Sensor(void) {}
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION1_SRC_SENSOR_H_
