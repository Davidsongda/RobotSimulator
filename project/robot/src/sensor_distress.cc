/**
 * @file sensor_distress.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include "src/sensor_distress.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorDistress::SensorDistress() :
    Sensor(),
    range_(0.0),
    isDistress_(0),
    sensor_pos(0.0, 0.0),
    sensed_pos(0.0, 0.0),
    sensed_radius(0.0) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/


void SensorDistress::Reset() {
  activated(0);
} /* reset() */

bool SensorDistress::IsRange(EventDistressCall * e) {
  double e1x = e->SensorPos().x;
  double e1y = e->SensorPos().y;
  double e2x = e->SensedPos().x;
  double e2y = e->SensedPos().y;
  double dist = std::sqrt(
    std::pow(e2x - e1x, 2) + std::pow(e2y - e1y, 2));
  if (dist > range_ + e->SensedRad()) {
    return false;
  } else {
    return true;
  }
}


void SensorDistress::Accept(EventDistressCall *const e) {
  if ( IsRange(e) ) {
    activated(1);
    sensor_pos = e->SensorPos();
    sensed_pos = e->SensedPos();
    sensed_radius = e->SensedRad();
    isDistress_ = 1;
  } else {
    activated(0);
  }
}


NAMESPACE_END(csci3081);
