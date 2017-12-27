/**
 * @file sensor_proximity.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/sensor_proximity.h"
#include <iostream>
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorProximity::SensorProximity() :
    Sensor(),
    distance_(50.0),
    sensor_pos(0.0, 0.0),
    sensed_pos(0.0, 0.0),
    sensed_radius(0.0),
    sensor_heading_angle(0),
    filed_of_view_(120.0) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

bool SensorProximity::InRange(Range r1, Range r2) {
  if (r1.lower > r1.upper) {
    r1 = {r1.upper, r1.lower};
  }
  if (r2.lower > r2.upper) {
    r1 = {r2.upper, r2.lower};
  }

  if ((r2.lower >= r1.lower && r2.lower <= r1.upper)
      || (r2.lower >= r1.lower + 360 && r2.lower <= r1.upper + 360)
      || (r2.lower >= r1.lower - 360 && r2.lower <= r1.upper - 360)) {
    return true;
  }
  if ((r2.upper >= r1.lower + 360 && r2.upper <= r1.upper + 360)
      || (r2.upper >= r1.lower && r2.upper <= r1.upper)
      || (r2.upper >= r1.lower - 360 && r2.upper <= r1.upper - 360)) {
    return true;
  }
  return false;
}

double SensorProximity::SensorReading(EventProximity * e) {
  double e1x = e->SensorPos().x;
  double e1y = e->SensorPos().y;
  double e2x = e->SensedPos().x;
  double e2y = e->SensedPos().y;
  double radius = e->SensedRad();
  double heading_angle_ = e->SensorHd();
  double deltaX = e2x - e1x;
  double deltaY = e2y - e1y;
  double dist = sqrt(deltaX * deltaX + deltaY * deltaY);
  if (dist > distance_ + radius) {
    return -1;
  }
  double triangle_theta = Positive(atan(radius / dist) * 180 / 3.14);
  double distance_theta = Positive(atan2(deltaY, deltaX) * 180 / 3.14);
  Range r1, r2;

  r1.lower = heading_angle_ - (filed_of_view_)/2;
  r1.upper =  heading_angle_ + (filed_of_view_)/2;

  r2.lower = distance_theta - triangle_theta;
  r2.upper = distance_theta + triangle_theta;
  if ( InRange(r1, r2) ) {
    return 1;
  } else {
    return -1;
  }
}

void SensorProximity::Accept(EventProximity *const e) {
  // Determine if the sensor is activated or deactivated.
  if ( SensorReading(e) == 1 ) {
    activated(1);
    sensed_pos = e->SensedPos();
    sensor_pos = e->SensorPos();
    sensed_radius = e->SensedRad();
    sensor_heading_angle = e->SensorHd();
  } else {
    activated(0);
  }
}

void SensorProximity::Reset() {
  activated(0);
  distance(0);
} /* reset() */

NAMESPACE_END(csci3081);
